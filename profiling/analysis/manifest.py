"""Read-only environment/process inventory. Run before and after each trial."""
import argparse
from datetime import datetime, timezone
import glob
import hashlib
import json
import os
from pathlib import Path
import platform
import subprocess

ROOT=Path(__file__).resolve().parents[2]

def read(path):
    try: return Path(path).read_text()
    except (OSError, UnicodeError) as e: return {'unavailable': str(e)}

def command(args):
    try:
        p=subprocess.run(args, cwd=ROOT, capture_output=True, text=True, timeout=15)
        return dict(command=args, returncode=p.returncode, stdout=p.stdout, stderr=p.stderr)
    except (OSError, subprocess.TimeoutExpired) as e: return {'unavailable':str(e)}

def sha(path):
    try:
        h=hashlib.sha256()
        with Path(path).open('rb') as f:
            for part in iter(lambda:f.read(1024*1024),b''): h.update(part)
        return h.hexdigest()
    except OSError as e: return {'unavailable':str(e)}

def process(pid,tid):
    p=Path('/proc')/str(pid); t=p/'task'/str(tid)
    status=read(t/'status'); stat=read(t/'stat')
    counters={}
    if isinstance(stat,str):
        fields=stat[stat.rfind(')')+2:].split()
        for name,index in [('minor_faults',7),('major_faults',9),('cpu',36)]: counters[name]=int(fields[index])
    for line in status.splitlines() if isinstance(status,str) else []:
        if line.startswith(('voluntary_ctxt_switches:','nonvoluntary_ctxt_switches:')):
            k,v=line.split(':'); counters[k]=int(v)
    try:
        scheduling=dict(policy=os.sched_getscheduler(tid),priority=os.sched_getparam(tid).sched_priority,
                        affinity=sorted(os.sched_getaffinity(tid)))
    except OSError as e: scheduling={'unavailable':str(e)}
    maps=read(p/'maps'); hashes={}
    if isinstance(maps,str):
        for line in maps.splitlines():
            name=line.split()[-1]
            if name.startswith('/') and ('.so' in name or 'runner' in name or 'control_node' in name): hashes[name]=sha(name)
    return dict(pid=pid,tid=tid,status=status,process_status=read(p/'status'),stat=stat,counters=counters,
                scheduling=scheduling,sched=read(t/'sched'),schedstat=read(t/'schedstat'),limits=read(p/'limits'),
                maps=maps,binary_library_hashes=hashes)

def environment():
    return dict(timestamp_utc=datetime.now(timezone.utc).isoformat(),kernel=platform.uname()._asdict(),
      kernel_realtime=read('/sys/kernel/realtime'),os_release=read('/etc/os-release'),
      git=command(['git','rev-parse','HEAD']),dirty=command(['git','status','--porcelain=v1']),
      compiler=command(['c++','--version']),cpu=command(['lscpu']),identity=command(['id']),
      ros_packages=command(['dpkg-query','-W','ros-humble-ros2-control','ros-humble-controller-manager','ros-humble-hardware-interface','ros-humble-controller-interface','ros-humble-ros-workspace']),
      igh=command(['/opt/etherlab/bin/ethercat','version']),igh_header_hash=sha('/opt/etherlab/include/ecrt.h'),
      igh_library_hash=sha('/opt/etherlab/lib/libethercat.so'),
      governors={p:read(p) for p in glob.glob('/sys/devices/system/cpu/cpu*/cpufreq/*') if Path(p).name in ('scaling_governor','scaling_cur_freq','scaling_min_freq','scaling_max_freq')},
      interrupts=read('/proc/interrupts'),interrupt_affinity={p:read(p) for p in glob.glob('/proc/irq/*/smp_affinity_list')},
      meminfo=read('/proc/meminfo'),master=command(['/opt/etherlab/bin/ethercat','master']),
      slaves=command(['/opt/etherlab/bin/ethercat','slaves']),domains=command(['/opt/etherlab/bin/ethercat','domains']),
      limits=read('/proc/self/limits'),perf=command(['perf','--version']))

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('output');p.add_argument('--pid',type=int);p.add_argument('--tid',type=int)
    p.add_argument('--build',type=Path);p.add_argument('--run-id',type=int,default=0);p.add_argument('--variant',type=int,default=0)
    p.add_argument('--level',choices=['OFF','COARSE','FINE'],default='OFF');p.add_argument('--diagnostics',choices=['production','quiet'],default='production')
    p.add_argument('--phase',default='preflight');p.add_argument('--binary',type=Path)
    a=p.parse_args()
    result=dict(run_id=a.run_id,variant=a.variant,profiling_level=a.level,diagnostic_mode=a.diagnostics,
                phase=a.phase,motion_occurred=None,synthetic=False,environment=environment())
    if a.pid: result['process']=process(a.pid,a.tid or a.pid)
    if a.binary: result['binary']=dict(path=str(a.binary.resolve()),sha256=sha(a.binary),ldd=command(['ldd',str(a.binary)]))
    if a.build: result['build_flags']={str(q):read(q) for q in a.build.rglob('flags.make')}
    output=Path(a.output);output.parent.mkdir(parents=True,exist_ok=True)
    output.write_text(json.dumps(result,indent=2,sort_keys=True)+'\n')
