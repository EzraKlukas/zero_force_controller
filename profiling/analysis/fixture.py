"""Generate tiny explicitly synthetic examples; never evidence of hardware timing."""
from pathlib import Path
import json
import numpy as np
from trace import FIELDS, HEADER, MAGIC

def generate(root):
    for variant, name in [(1,'synthetic-standalone'), (2,'synthetic-cm')]:
        path=Path(root)/name; path.mkdir(parents=True, exist_ok=True)
        rows=[]
        for i in range(12):
            base=10_000_000_000+i*1_000_000+(100 if i%2 else 0)
            d=dict.fromkeys(FIELDS,0)
            d.update(schema=1, run_id=variant, variant=variant, level=2, cycle=i, phase=3, controller_active=1,
                     deadline_mono_ns=base+200_000, cycle_mono_ns=base+200_030, write_exit_mono_ns=base+225_000,
                     actual_period_ns=(1_000_100 if i%2 else 999900) if i else 0,
                     ros_period_ns=1_000_000, ready=1, wc=4, wc_state=2, statusword=0x1237, mode=8,
                     actual_counts=123, target_counts=123, reference_sync=int(i%2==0), cpu=2)
            stamps=dict(cycle_entry=0,cm_read_entry=1000,hardware_read_entry=2000,core_read_entry=3000,
                        core_read_exit=15000,hardware_read_exit=17000,cm_read_exit=17500,cm_update_entry=18000,
                        controller_entry=18500,calculation_entry=19000,calculation_exit=19200,controller_exit=19700,
                        cm_update_exit=20000,cm_write_entry=20500,hardware_write_entry=21000,core_write_entry=22000,
                        core_write_exit=24000,hardware_write_exit=25000,cm_write_exit=25500,sleep_entry=26000,
                        commit_entry=26100,commit_exit=26500,sleep_exit=1_000_000)
            d.update({k:base+v for k,v in stamps.items()})
            d.update(application_time_ns=100,receive_api_ns=5000,domain_process_ns=800,elm_decode_ns=400,
                     motor_decode_ns=300,state_poll_ns=4000,readiness_ns=100,encode_ns=100,
                     reference_sync_ns=100 if i%2==0 else 0,slave_sync_ns=200,domain_queue_ns=200,send_api_ns=1000)
            if variant==1:
                for k in ('cm_read_entry','cm_read_exit','cm_update_entry','cm_update_exit','cm_write_entry','cm_write_exit','sleep_entry','sleep_exit'): d[k]=0
            rows.append([d[k] for k in FIELDS])
        with (path/'timing.bin').open('wb') as f:
            f.write(HEADER.pack(MAGIC,1,len(FIELDS)*8,len(rows),0,2,len(FIELDS),0))
            f.write(np.asarray(rows,dtype='<i8').tobytes())
        (path/'manifest.json').write_text(json.dumps(dict(run_id=variant,variant=variant,profiling_level='FINE',diagnostic_mode='production',phase='synthetic steady hold',motion_occurred=False,synthetic=True,environment={'source':'deterministic artificial fixture; no physical measurements'}),indent=2)+'\n')
if __name__=='__main__':
    import sys
    generate(sys.argv[1])
