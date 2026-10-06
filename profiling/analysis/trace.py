"""Version 2 trace reader; one schema definition shared with C++. Integer ns."""
from pathlib import Path
import argparse
import json
import re
import struct
import numpy as np
import pandas as pd

ROOT = Path(__file__).resolve().parents[2]
FIELDS = re.findall(r"ZFC_TIMING_FIELD\((\w+)\)", (ROOT / "packages/zfc_timing/include/timing_fields.inc").read_text())
HEADER = struct.Struct("<8q")
MAGIC = 0x5A464354494D4531
PERIOD = 1_000_000


def read_trace(path):
    path = Path(path)
    with path.open("rb") as f:
        header = f.read(HEADER.size)
        if len(header) != HEADER.size:
            raise ValueError("truncated header")
        magic, schema, size, count, drops, level, columns, reserved = HEADER.unpack(header)
        if (magic, schema, size, columns, reserved) != (MAGIC, 2, len(FIELDS)*8, len(FIELDS), 0):
            raise ValueError("unsupported trace layout/endian/schema")
        if count < 0 or drops < 0 or level not in (1, 2):
            raise ValueError("invalid header values")
        if path.stat().st_size != HEADER.size + count*size:
            raise ValueError("truncated trace or trailing bytes")
        values = np.fromfile(f, dtype="<i8", count=count*columns).reshape(count, columns)
    df = pd.DataFrame(values, columns=FIELDS)
    if count:
        if not (df.schema.eq(schema).all() and df.level.eq(level).all()):
            raise ValueError("mixed schemas/levels")
        if df.cycle.diff().dropna().le(0).any() or df.cycle_entry.diff().dropna().le(0).any():
            raise ValueError("nonmonotonic cycles/timestamps")
        if df.run_id.nunique() != 1:
            raise ValueError("mixed runs")
        if df.trace_drops.lt(0).any() or df.trace_drops.diff().dropna().lt(0).any():
            raise ValueError("invalid drop counters")
        selected = df[df.hardware_read_entry.gt(0)]
        if not np.array_equal(selected.hardware_read_entry.diff().iloc[1:].to_numpy(), selected.actual_period_ns.iloc[1:].to_numpy()):
            raise ValueError("actual period does not match read entries")
    return df, dict(schema=schema, record_bytes=size, records=count, trace_drops=drops,
                    level=level, missing_cycles=int(df.cycle.diff().sub(1).clip(lower=0).sum()))


def duration(df, start, end):
    valid = df[start].gt(0) & df[end].ge(df[start])
    return (df[end]-df[start]).where(valid)


def metrics(df):
    d = df.copy()
    d['period_error_ns'] = (d.actual_period_ns-PERIOD).where(d.actual_period_ns.gt(0))
    d['active_span_ns'] = duration(d, 'hardware_read_entry', 'hardware_write_exit')
    d['execution_ns'] = duration(d, 'cycle_entry', 'sleep_entry')
    d['budget_slack_ns'] = PERIOD-d.execution_ns
    d['execution_overrun'] = d.execution_ns.gt(PERIOD).where(d.execution_ns.notna())
    d['wakeup_lateness_ns'] = (d.cycle_mono_ns-d.deadline_mono_ns).where(d.deadline_mono_ns.gt(0))
    d['completion_lateness_ns'] = (d.execution_end_mono_ns-d.deadline_mono_ns-PERIOD).where(d.deadline_mono_ns.gt(0) & d.execution_end_mono_ns.gt(0))
    d['deadline_miss'] = d.completion_lateness_ns.gt(0).where(d.completion_lateness_ns.notna())
    for name, a, b in [('core_read_ns','core_read_entry','core_read_exit'), ('core_write_ns','core_write_entry','core_write_exit'),
                       ('hardware_read_ns','hardware_read_entry','hardware_read_exit'), ('hardware_write_ns','hardware_write_entry','hardware_write_exit'),
                       ('controller_ns','controller_entry','controller_exit'), ('calculation_ns','calculation_entry','calculation_exit'),
                       ('profile_commit_ns','commit_entry','commit_exit'), ('sleep_wait_ns','sleep_entry','sleep_exit')]:
        d[name] = duration(d,a,b)
    d['read_adapter_ns'] = d.hardware_read_ns-d.core_read_ns
    d['write_adapter_ns'] = d.hardware_write_ns-d.core_write_ns
    d['controller_wrapper_ns'] = d.controller_ns-d.calculation_ns
    d['cpu_migration'] = d.cpu.ne(d.cpu.shift()).astype(int)
    if len(d): d.loc[d.index[0], 'cpu_migration'] = 0
    return d


# Exhaustive mutually exclusive partition cycle_entry -> sleep_entry, only
# for CM cycles with exactly one active controller and one hardware component.
def cm_partition(d):
    stage = pd.DataFrame(index=d.index)
    stage['pre_read_bookkeeping'] = duration(d,'cycle_entry','cm_read_entry')
    stage['read_wrapper'] = duration(d,'cm_read_entry','hardware_read_entry') + duration(d,'hardware_read_exit','cm_read_exit')
    stage['hardware_read'] = duration(d,'hardware_read_entry','hardware_read_exit')
    stage['read_to_controller_dispatch'] = duration(d,'cm_read_exit','controller_entry')
    stage['controller'] = duration(d,'controller_entry','controller_exit')
    stage['remaining_update'] = duration(d,'controller_exit','cm_update_exit')
    stage['update_to_write_dispatch'] = duration(d,'cm_update_exit','hardware_write_entry')
    stage['hardware_write'] = duration(d,'hardware_write_entry','hardware_write_exit')
    stage['remaining_write'] = duration(d,'hardware_write_exit','cm_write_exit')
    stage['post_write_bookkeeping'] = duration(d,'cm_write_exit','sleep_entry')
    valid = stage.notna().all(axis=1)
    if valid.any() and not np.array_equal(stage.loc[valid].sum(axis=1).to_numpy(), (d.sleep_entry-d.cycle_entry)[valid].to_numpy()):
        raise ValueError('partition does not close')
    return stage.where(valid)


def summary(series):
    s = series.dropna()
    if s.empty: return {'n': 0}
    return dict(n=len(s), mean=s.mean(), std=s.std(), median=s.median(),
                MAD=(s-s.median()).abs().median(), p90=s.quantile(.9), p99=s.quantile(.99),
                p99_9=s.quantile(.999) if len(s)>=1000 else np.nan,
                p99_99=s.quantile(.9999) if len(s)>=10000 else np.nan, maximum=s.max())


def load_run(directory):
    path = Path(directory)
    manifest = json.loads((path/'manifest.json').read_text())
    for key in ('run_id', 'profiling_level', 'diagnostic_mode', 'phase', 'motion_occurred', 'synthetic', 'environment'):
        if key not in manifest: raise ValueError(f'manifest missing {key}')
    d, integrity = read_trace(path/'timing.bin')
    if len(d) and (not d.run_id.eq(manifest['run_id']).all()):
        raise ValueError('manifest/trace identity mismatch')
    return metrics(d), manifest, integrity

if __name__ == '__main__':
    p = argparse.ArgumentParser(); p.add_argument('input'); p.add_argument('output')
    args = p.parse_args()
    d, info = read_trace(args.input)
    d.to_csv(args.output, index=False)
    print(json.dumps(info, sort_keys=True))
