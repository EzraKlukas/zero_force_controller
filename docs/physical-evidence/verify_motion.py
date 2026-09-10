"""Replay recorded evidence only. No ROS, IgH, services, or hardware access."""
from pathlib import Path
import json

base = Path(__file__).resolve().parent
records = [
    dict(field.split("=", 1) for field in line.split("ZFC ", 1)[1].split())
    for line in (base / "single-motion.log.txt").read_text().splitlines()
    if "ZFC " in line
]
assert all(r["reason"] == "none" and r["dropped"] == "0" for r in records)
starts = [r for r in records if r["event"] == "motion-start"]
assert len(starts) == 1
start = starts[0]
origin = int(start["actual"])
assert int(start["target"]) == origin
commands = [r for r in records if r["event"] == "motion-command"]
assert len(commands) == 2000
for i, record in enumerate(commands, 1):
    assert int(record["changes"]) == i
    assert int(record["target"]) == origin + 10 * (i if i <= 1000 else 2000 - i)
    if i > 1:
        assert int(record["writes"]) == int(commands[i - 2]["writes"]) + 1
for record in records:
    if record["phase"] != "active":
        continue
    for key, expected in {
        "link": "1", "slaves": "3", "wc": "4", "wc_state": "2",
        "ek": "1/1/8", "elm": "1/1/8", "drive": "1/1/8",
        "cia": "4", "mode": "8", "limits": "0/0", "ready": "1",
        "excessive_periods": "0",
    }.items():
        assert record[key] == expected, (key, record)
    for axis in ("x", "y", "z"):
        sample = record[axis].split("/")
        assert int(sample[1]) > 0 and sample[3:5] == ["0", "0"]
ready = next(r for r in records if r["event"] == "startup-ready")
assert int(start["mono_ns"]) - int(ready["mono_ns"]) >= 30_000_000_000
holds = [
    r for r in records if r["event"] == "status"
    and r["claimed"] == "1" and r["changes"] == "2000"
]
assert len(holds) >= 3
assert all(int(r["target"]) == origin and abs(int(r["actual"]) - origin) <= 10 for r in holds)
assert int(holds[-1]["actual"]) == origin
shutdown = [r for r in records if r["event"] == "shutdown-confirmed"]
assert len(shutdown) == 1 and shutdown[0]["cia"] == "1" and shutdown[0]["wc_state"] == "2"
result = json.loads((base / "single-motion-results.json").read_text())
assert result["activation"] == start
assert result["reversal"] == commands[999]
assert result["command_return"] == commands[-1]
assert result["final_hold"] == holds[-1]
print(f"PASS: one activation, +10 x 1000, -10 x 1000, target {origin} -> {origin + 10000} -> {origin}")
print(f"PASS: actual returns to {origin}; {len(holds)} final hold samples; all active samples ready, WC complete, no faults")
print(f"Shutdown: voltage disabled, actual {shutdown[0]['actual']} (post-disable displacement retained)")
