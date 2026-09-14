#!/usr/bin/env bash
set -euo pipefail
cd /home/jetson/ezra-zfc
# ROS setup scripts do not support nounset.
set +u
source /opt/ros/humble/setup.bash
set -u
export ROS_LOCALHOST_ONLY=1
export ROS_LOG_DIR=/tmp/zfc-profiling-offline-ros-log
for mode in OFF COARSE FINE; do
  lower=${mode,,}
  cmake -S . -B "build/profiling-$lower" -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DZFC_PROFILING="$mode" > "profiling/results/preflight/root-$lower-final.log" 2>&1
  cmake --build "build/profiling-$lower" -j2 >> "profiling/results/preflight/root-$lower-final.log" 2>&1
  ctest --test-dir "build/profiling-$lower" --output-on-failure > "profiling/results/preflight/root-$lower-tests.txt" 2>&1
  colcon build --cmake-force-configure --base-paths packages --build-base "build/profiling-$lower-colcon" --install-base "build/profiling-$lower-install" --executor sequential --cmake-args -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo -DZFC_PROFILING="$mode" > "profiling/results/preflight/$lower-final-build.log" 2>&1
  (
    set +u
    source "build/profiling-$lower-install/setup.bash"
    set -u
    colcon test --base-paths packages --build-base "build/profiling-$lower-colcon" --install-base "build/profiling-$lower-install" --executor sequential > "profiling/results/preflight/$lower-final-tests.log" 2>&1
    colcon test-result --test-result-base "build/profiling-$lower-colcon" > "profiling/results/preflight/$lower-final-summary.txt"
  )
  echo "$mode complete"
done
python3 -m unittest discover -s profiling/analysis -p 'test_*.py'
