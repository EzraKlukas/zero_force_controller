from dataclasses import asdict
import importlib.util
from pathlib import Path
import sys
from types import SimpleNamespace as NS
import numpy as np
import pandas as pd
import pytest

# Pure tests work both from source and colcon, without a ROS overlay.
sys.path.insert(0, str(Path(__file__).parents[1]))
from zfc_calibration_analysis.analysis import Capture, Criteria, FIELDS, fit_samples, save_trial, reserve_trial


def fixture(slope=.25, bias=2.4525, noise=0.):
    a = np.repeat([.2, -.2, .4, -.4, .8, -.8, 1.2, -1.2], 200)
    rng = np.random.default_rng(71)
    return pd.DataFrame(dict(sequence=np.arange(1, len(a)+1), time_ns=np.arange(len(a), dtype=np.int64)*1000000,
                             phase=10, position_m=0., velocity_mps=.05,
                             force_n=bias+slope*a+rng.normal(0, noise, len(a)),
                             reference_position_m=0., reference_velocity_mps=.05,
                             reference_acceleration_mps2=a))


@pytest.mark.parametrize('bias,noise', [(0., 0.), (12., .002), (-5., .005)])
def test_linear_bias_noise(bias, noise):
    fit, plateaus = fit_samples(fixture(bias=bias, noise=noise))
    assert fit.valid, fit.reason
    assert abs(fit.inertial_force_coefficient_kg-.25) < .003
    assert abs(fit.intercept_n-bias) < .002
    assert fit.plateau_count == 8 and fit.sample_count < 1600
    assert fit.uncertainty_kg >= 0 and len(plateaus) == 8


def test_signed_force_path_is_explicit():
    assert not fit_samples(fixture(slope=-.25))[0].valid
    assert fit_samples(fixture(slope=-.25), Criteria(expected_coefficient_sign=-1))[0].valid


@pytest.mark.parametrize('corruption', ['coverage', 'sequence', 'nan', 'time', 'tracking', 'velocity', 'residual', 'polarity', 'identity'])
def test_invalid_fit(corruption):
    frame = fixture()
    if corruption == 'coverage':
        frame.reference_acceleration_mps2 = abs(frame.reference_acceleration_mps2)
    elif corruption == 'sequence':
        frame.loc[7, 'sequence'] += 1
    elif corruption == 'nan':
        frame.loc[7, 'force_n'] = np.nan
    elif corruption == 'time':
        frame.loc[7, 'time_ns'] = 0
    elif corruption == 'tracking':
        frame.position_m = .1
    elif corruption == 'velocity':
        frame.velocity_mps = .3
    elif corruption == 'residual':
        frame.force_n += np.random.default_rng(3).normal(0, .2, len(frame))
    elif corruption == 'polarity':
        frame.loc[frame.reference_acceleration_mps2 < 0, 'force_n'] = 2.4525-.25*frame.reference_acceleration_mps2
    else:
        frame['trial_id'] = 7
        frame.loc[7, 'trial_id'] = 8
    assert not fit_samples(frame)[0].valid


def sample(seq=1, trial=7, ns=None):
    ns = seq*1000000 if ns is None else ns
    return NS(sequence=seq, trial_id=trial, stamp=NS(sec=0, nanosec=ns), valid=True, fault_code=0,
              phase=10, **{k: 0. for k in FIELDS[3:]})


def batch(*samples, dropped=0):
    return NS(samples=samples, dropped_samples=dropped, failed_publication_samples=0)


@pytest.mark.parametrize('kind', ['identity', 'gap', 'time', 'overflow', 'drops', 'nan', 'fault'])
def test_capture_rejection(kind):
    c = Capture(7, maximum_samples=1 if kind == 'overflow' else 10)
    c.batch(batch(sample()))
    m = sample(3 if kind == 'gap' else 2, trial=8 if kind == 'identity' else 7,
               ns=0 if kind == 'time' else None)
    if kind == 'nan':
        m.force_n = float('nan')
    if kind == 'fault':
        m.fault_code = 1
    c.batch(batch(m, dropped=int(kind == 'drops')))
    assert c.error


def test_completion_requires_final_sequence_and_preserves_early_samples():
    c = Capture(7)
    c.batch(batch(sample()))
    c.finish(NS(trial_id=7, final_sequence=2, dropped_samples=0, failed_publication_samples=0,
                completed=True, successful=True, capture_complete=True))
    assert not c.drained
    c.batch(batch(sample(2)))
    assert c.drained and c.rows[0][0] == 1 and c.rows[-1][0] == 2


def test_offline_save_replay_and_incomplete(tmp_path):
    frame = fixture()
    metadata = dict(trial_id=7, backend='gazebo')
    fit = save_trial(tmp_path, frame[list(FIELDS)].itertuples(index=False, name=None), metadata, Criteria())
    assert fit.valid and (tmp_path/'regression.png').exists()
    assert fit_samples(pd.read_csv(tmp_path/'samples.csv'))[0].inertial_force_coefficient_kg == pytest.approx(.25)
    invalid = save_trial(tmp_path, tuple(), metadata, Criteria(), 'canceled')
    assert not invalid.valid and invalid.reason == 'canceled'


def test_trial_reservation_is_exclusive(tmp_path):
    path = tmp_path/'7'
    reserve_trial(path)
    (path/'evidence').write_text('preserve')
    with pytest.raises(FileExistsError):
        reserve_trial(path)
    assert (path/'evidence').read_text() == 'preserve'
