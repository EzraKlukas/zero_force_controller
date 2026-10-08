#!/usr/bin/env bash
# Offline build/test matrix. Does not launch nodes or access EtherCAT hardware.
set -eo pipefail
cd "$(dirname "$0")/../.."
source /opt/ros/humble/setup.bash
export ROS_LOCALHOST_ONLY=1
export ROS_LOG_DIR=/tmp/zfc-profiling-offline-ros-log
# Default Distrobox matrix excludes genuine hardware/SDK packages.
hardware_args=(--packages-ignore zfc_ethercat_core zfc_ethercat_hardware)
if [[ ${ZFC_WITH_IGH:-0} == 1 ]]; then hardware_args=(); fi
for mode in OFF COARSE FINE; do
  lower=${mode,,}
  colcon build --base-paths packages "${hardware_args[@]}" --build-base "build/profiling-$lower-colcon" \
    --install-base "build/profiling-$lower-install" --executor sequential \
    --cmake-args -DBUILD_TESTING=ON -DZFC_PROFILING="$mode"
  (
    source "build/profiling-$lower-install/setup.bash"
    colcon test --base-paths packages "${hardware_args[@]}" --build-base "build/profiling-$lower-colcon" \
      --install-base "build/profiling-$lower-install" --executor sequential
    colcon test-result --test-result-base "build/profiling-$lower-colcon"
  )
done
python3 -m unittest discover -s profiling/analysis -p 'test_*.py'
