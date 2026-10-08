"""Pure fitting and bounded source-sequence validation, also used offline.

Force is regressed ONLY against the captured effective commanded acceleration.
Measured velocity is a tracking check, never a replacement regressor. Plateaus
are independent fitting units; control-rate samples are not independent trials.
"""
import argparse
from dataclasses import dataclass, asdict
import json
import math
from pathlib import Path
import numpy as np
import pandas as pd
import yaml

FIELDS = ('sequence', 'time_ns', 'phase', 'position_m', 'velocity_mps', 'force_n',
          'reference_position_m', 'reference_velocity_mps', 'reference_acceleration_mps2')
SOURCE = 'sequencer effective commanded acceleration; nominal dt=0.001 s'


@dataclass(frozen=True)
class Criteria:
    maximum_gap_s: float = .01
    expected_coefficient_sign: int = 1
    minimum_acceleration_mps2: float = .1
    maximum_acceleration_mps2: float = 2.1
    plateau_settle_s: float = .05
    plateau_end_guard_s: float = .01
    reversal_guard_s: float = .02
    minimum_plateau_samples: int = 8
    minimum_plateaus_per_branch: int = 3
    minimum_r_squared: float = .95
    maximum_residual_rms_n: float = .05
    maximum_branch_difference_fraction: float = .15
    maximum_coefficient_kg: float = 10.
    maximum_tracking_error_m: float = .002
    maximum_velocity_error_mps: float = .025

    def validate(self):
        values = asdict(self)
        if not all(math.isfinite(v) for v in values.values()):
            raise ValueError('non-finite fitting criterion')
        if self.expected_coefficient_sign not in (-1, 1):
            raise ValueError('expected_coefficient_sign must be +1 or -1')
        for name, value in values.items():
            if name != 'expected_coefficient_sign' and value <= 0:
                raise ValueError(name+' must be positive')
        if self.minimum_r_squared >= 1 or self.maximum_acceleration_mps2 <= self.minimum_acceleration_mps2:
            raise ValueError('invalid R² or acceleration interval')


@dataclass
class Fit:
    valid: bool = False
    reason: str = 'not analyzed'
    inertial_force_coefficient_kg: float = 0.
    intercept_n: float = 0.
    r_squared: float = 0.
    residual_rms_n: float = 0.
    uncertainty_kg: float = 0.
    sample_count: int = 0
    plateau_count: int = 0
    positive_slope_kg: float = 0.
    negative_slope_kg: float = 0.
    tracking_rms_m: float = 0.
    acceleration_source: str = SOURCE


class Capture:
    """Append under coordinator's callback lock; bounded, no arrival-time joins."""
    def __init__(self, trial_id, maximum_samples=120000, maximum_gap_s=.01):
        self.trial_id = trial_id
        self.maximum_samples = maximum_samples
        self.maximum_gap_ns = round(maximum_gap_s*1e9)
        self.rows = []
        self.error = ''
        self.dropped = 0
        self.final_sequence = 0
        self.terminal = None

    def batch(self, batch):
        self.dropped = max(self.dropped, batch.dropped_samples+batch.failed_publication_samples)
        if self.dropped:
            self.error = 'controller queue overflow or failed publication'
        for m in batch.samples:
            if self.error:
                break
            ns = m.stamp.sec*1000000000+m.stamp.nanosec
            if m.trial_id != self.trial_id:
                self.error = 'unexpected trial identity'
            elif m.sequence != len(self.rows)+1:
                self.error = 'missing, duplicate or out-of-order source sequence'
            elif len(self.rows) >= self.maximum_samples:
                self.error = 'bounded recording capacity exceeded'
            elif not m.valid or m.fault_code:
                self.error = 'invalid controller feedback or fault'
            elif not all(math.isfinite(getattr(m, f)) for f in FIELDS[3:]):
                self.error = 'non-finite synchronized sample'
            elif self.rows and (ns < self.rows[-1][1] or
                                (ns == self.rows[-1][1] and m.sequence != 2)):
                self.error = 'source simulation time restarted, reversed or repeated'
            elif self.rows and ns-self.rows[-1][1] > self.maximum_gap_ns:
                self.error = 'source time gap exceeded criterion'
            if self.error:
                break
            self.rows.append((m.sequence, ns, m.phase, *(getattr(m, f) for f in FIELDS[3:])))

    def finish(self, status):
        if status.trial_id != self.trial_id:
            self.error = 'terminal trial identity mismatch'
            return
        self.terminal = status
        self.final_sequence = status.final_sequence
        self.dropped = max(self.dropped, status.dropped_samples+status.failed_publication_samples)
        if not (status.completed and status.successful and status.capture_complete) or self.dropped:
            self.error = 'unsuccessful or incomplete controller terminal status'

    @property
    def drained(self):
        return bool(self.terminal and not self.error and self.final_sequence == len(self.rows))


def fit_samples(frame, criteria=Criteria()):
    criteria.validate()
    result = Fit()
    def reject(reason):
        result.reason = reason
        return result, pd.DataFrame()
    if len(frame) < 2 or any(f not in frame for f in FIELDS):
        return reject('missing capture columns or samples')
    data = frame[list(FIELDS)].to_numpy(dtype=float)
    if not np.isfinite(data).all():
        return reject('non-finite capture')
    if 'trial_id' in frame and (frame.trial_id.nunique() != 1 or frame.trial_id.iloc[0] <= 0):
        return reject('mixed or invalid trial identity')
    if not np.array_equal(frame.sequence.to_numpy(), np.arange(1, len(frame)+1)):
        return reject('incomplete or unordered sequence')
    # Keep int64 timestamps until subtraction (wall-clock ROS times can be large).
    ns = frame.time_ns.to_numpy(dtype=np.int64)
    delta = np.diff(ns)
    if np.any(delta < 0) or np.any(delta[1:] <= 0) or np.any(delta > criteria.maximum_gap_s*1e9):
        return reject('non-monotonic source time or excessive gaps')
    t = (ns-ns[0])*1e-9
    a = frame.reference_acceleration_mps2.to_numpy()
    v = frame.reference_velocity_mps.to_numpy()
    f = frame.force_n.to_numpy()
    qerr = frame.position_m.to_numpy()-frame.reference_position_m.to_numpy()
    result.tracking_rms_m = float(np.sqrt(np.mean(qerr*qerr)))
    if np.max(np.abs(qerr)) > criteria.maximum_tracking_error_m:
        return reject('position tracking exceeds tolerance')
    # Split at phase or effective acceleration changes, including clipping spikes.
    changes = np.r_[0, np.flatnonzero((np.abs(np.diff(a)) > 1e-6) |
                                    (np.diff(frame.phase.to_numpy()) != 0))+1, len(frame)]
    reversals = t[1:][v[:-1]*v[1:] <= 0]
    plateau_rows, selected = [], []
    for start, end in zip(changes[:-1], changes[1:]):
        if frame.phase.iloc[start] != 10 or not criteria.minimum_acceleration_mps2-1e-6 <= abs(a[start]) <= criteria.maximum_acceleration_mps2:
            continue
        indices = np.arange(start, end)
        mask = (t[indices] >= t[start]+criteria.plateau_settle_s) & (t[indices] <= t[end-1]-criteria.plateau_end_guard_s)
        for reversal in reversals[(reversals >= t[start]-.1) & (reversals <= t[end-1]+.1)]:
            mask &= np.abs(t[indices]-reversal) >= criteria.reversal_guard_s
        indices = indices[mask]
        if len(indices) < criteria.minimum_plateau_samples:
            continue
        verr = frame.velocity_mps.to_numpy()[indices]-v[indices]
        if np.max(np.abs(verr)) > criteria.maximum_velocity_error_mps:
            return reject('velocity tracking exceeds tolerance on acceleration plateaus')
        plateau_rows.append((float(np.mean(a[indices])), float(np.mean(f[indices])), len(indices), float(t[indices[0]]), float(t[indices[-1]])))
        selected.extend(indices)
    plateaus = pd.DataFrame(plateau_rows, columns=['acceleration_mps2', 'force_n', 'samples', 'start_s', 'end_s'])
    result.plateau_count, result.sample_count = len(plateaus), len(selected)
    if not len(plateaus):
        return reject('no settled acceleration plateaus')
    x, y = plateaus.acceleration_mps2.to_numpy(), plateaus.force_n.to_numpy()
    def slope(xb, yb):
        return float(np.linalg.lstsq(np.column_stack((np.ones(len(xb)), xb)), yb, rcond=None)[0][1])
    for sign in (-1, 1):
        xb = x[x*sign > 0]
        if len(xb) < criteria.minimum_plateaus_per_branch or len(np.unique(np.round(xb, 5))) < 3:
            return reject('inadequate positive/negative acceleration coverage (three distinct levels required)')
    matrix = np.column_stack((np.ones(len(x)), x))
    b, k = np.linalg.lstsq(matrix, y, rcond=None)[0]
    residual = y-(b+k*x)
    denominator = np.sum((y-np.mean(y))**2)
    result.intercept_n, result.inertial_force_coefficient_kg = float(b), float(k)
    result.r_squared = float(1-np.sum(residual**2)/denominator) if denominator > 0 else 0.
    result.residual_rms_n = float(np.sqrt(np.mean((f[selected]-b-k*a[selected])**2)))
    # Standard error across plateau means, not fictitious 1 kHz independent samples.
    result.uncertainty_kg = float(np.sqrt(np.sum(residual**2)/(len(x)-2)*np.linalg.inv(matrix.T@matrix)[1, 1]))
    result.positive_slope_kg = slope(x[x > 0], y[x > 0])
    result.negative_slope_kg = slope(x[x < 0], y[x < 0])
    if not all(math.isfinite(value) for value in asdict(result).values() if isinstance(value, (float, int))):
        return reject('non-finite fit')
    if k*criteria.expected_coefficient_sign <= 0 or abs(k) > criteria.maximum_coefficient_kg:
        return reject('coefficient sign or magnitude inconsistent with reviewed force path')
    if result.positive_slope_kg*criteria.expected_coefficient_sign <= 0 or result.negative_slope_kg*criteria.expected_coefficient_sign <= 0 or abs(result.positive_slope_kg-result.negative_slope_kg) > abs(k)*criteria.maximum_branch_difference_fraction:
        return reject('positive/negative branches have inconsistent polarity or slope')
    if result.r_squared < criteria.minimum_r_squared or result.residual_rms_n > criteria.maximum_residual_rms_n:
        return reject('poor R² or gross force residuals')
    result.valid, result.reason = True, 'accepted settled-plateau effective force/acceleration fit'
    return result, plateaus


def save_trial(directory, rows, metadata, criteria, incomplete_reason=''):
    """Worker-only file I/O. Metadata file is the final durable worker acknowledgment."""
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    frame = pd.DataFrame(rows, columns=FIELDS)
    frame.insert(0, 'trial_id', metadata['trial_id'])
    frame.to_csv(directory/'samples.csv', index=False)
    fit, plateaus = (Fit(reason=incomplete_reason), pd.DataFrame()) if incomplete_reason else fit_samples(frame, criteria)
    plateaus.to_csv(directory/'plateaus.csv', index=False)
    document = dict(metadata, criteria=asdict(criteria), fit=asdict(fit), complete=not bool(incomplete_reason))
    (directory/'metadata.json').write_text(json.dumps(document, indent=2, allow_nan=False))
    (directory/'result.yaml').write_text(yaml.safe_dump({
        'schema_version': 1, 'units': {'inertial_force_coefficient_kg': 'kg', 'intercept_n': 'N'},
        'provenance': {'trial_id': metadata['trial_id'], 'backend': metadata['backend'],
                       'acceleration_source': SOURCE, 'model': metadata.get('model', {})},
        'fit': asdict(fit)}, sort_keys=False))
    if not frame.empty:
        import matplotlib
        matplotlib.use('Agg')
        import matplotlib.pyplot as plt
        fig, axes = plt.subplots(2, 1, figsize=(9, 7))
        t = (frame.time_ns-frame.time_ns.iloc[0])*1e-9
        axes[0].plot(t, frame.force_n, label='captured force.x (N)')
        axes[0].plot(t, fit.intercept_n+fit.inertial_force_coefficient_kg*frame.reference_acceleration_mps2, label='b + k_a a_reference')
        axes[0].set_ylim(float(frame.force_n.min())-.2, float(frame.force_n.max())+.2)
        axes[0].legend(); axes[0].set_xlabel('source time (s)')
        if not plateaus.empty:
            axes[1].scatter(plateaus.acceleration_mps2, plateaus.force_n, label='settled plateau means')
            xx = np.array([-2., 2.])
            axes[1].plot(xx, fit.intercept_n+fit.inertial_force_coefficient_kg*xx)
        axes[1].set_xlabel('effective commanded acceleration (m/s²)'); axes[1].set_ylabel('force.x (N)')
        fig.suptitle(f'Trial {metadata["trial_id"]}: {fit.reason}')
        fig.tight_layout(); fig.savefig(directory/'regression.png'); plt.close(fig)
    return fit


def reserve_trial(directory):
    """Exclusive owned directory before motion; never overwrite another trial."""
    path = Path(directory)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.mkdir(exist_ok=False)


def offline_main():
    parser = argparse.ArgumentParser(description='Replay the SAME pure plateau fit, without ROS or notebooks')
    parser.add_argument('trial_directory')
    args = parser.parse_args()
    directory = Path(args.trial_directory)
    metadata = json.loads((directory/'metadata.json').read_text())
    if not metadata['complete']:
        raise SystemExit('Refusing incomplete capture: '+metadata['fit']['reason'])
    frame = pd.read_csv(directory/'samples.csv')
    counts = metadata['capture_counts']
    if len(frame) != counts['final_sequence'] or counts['dropped'] or 'trial_id' not in frame or not frame.trial_id.eq(metadata['trial_id']).all():
        raise SystemExit('Incomplete capture or metadata/trial identity mismatch')
    fit, _ = fit_samples(frame, Criteria(**metadata['criteria']))
    print(json.dumps(asdict(fit), indent=2))
    raise SystemExit(0 if fit.valid else 1)


def save_application(directory, applied, zero_active, coefficient):
    """Separate worker acknowledgment of checked service/handoff outcomes."""
    path = Path(directory)/'metadata.json'
    document = json.loads(path.read_text())
    document['application'] = {'applied_atomically': applied, 'zero_force_active_after': zero_active,
                               'readback_coefficient_kg': coefficient}
    path.write_text(json.dumps(document, indent=2, allow_nan=False))
