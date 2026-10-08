# Decimated visualization only. Original full-rate batches remain authoritative.
std_msgs/Header header
ControllerState state
# Reconstructed outside update from force - frozen baseline - residual.
# Meaningful only in compliant phase; zero in capture/calibration phases.
float64 inertial_compensation_n
