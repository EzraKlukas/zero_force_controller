"""Small backend prerequisites. No hardware access, fitting or ROS fake backend."""
import hashlib
import math
from pathlib import Path
import yaml


def reviewed_profiles(settings):
    if not settings['installation_reviewed'] or not settings['controllers_reviewed'] or not settings['analysis_reviewed']:
        raise ValueError('review installation calibration, controller settings, and physical analysis criteria before preparation')
    for key in ('coordinate_convention', 'force_convention', 'calibration_profile_id'):
        if not settings[key].strip():
            raise ValueError('missing reviewed '+key)
    documents, hashes = {}, {}
    for key in ('installation_file', 'controllers_file', 'hardware_file'):
        path = Path(settings[key])
        if not path.is_absolute():
            raise ValueError(key+' must be the absolute profile used by physical launch')
        content = path.read_bytes()
        documents[key] = yaml.safe_load(content)
        hashes[key] = hashlib.sha256(content).hexdigest()
        if settings[key+'_sha256'] != hashes[key]:
            raise ValueError(key+' changed since launch; restart with reviewed profiles')
    installation = documents['installation_file']
    if installation.get('conventions_confirmed') is not True:
        raise ValueError('installation conventions_confirmed must be reviewed true')
    for key in ('m_per_count', 'force_x_newtons_per_count', 'force_y_newtons_per_count', 'force_z_newtons_per_count'):
        value = installation.get(key)
        if isinstance(value, bool) or not isinstance(value, (int, float)) or not math.isfinite(value) or value == 0:
            raise ValueError('missing finite nonzero signed installation '+key)
    if installation.get('force_frame') != 'load_cell_link' or installation.get('force_channel_mapping') != 'x,y,z':
        raise ValueError('installation force frame/channel mapping unsupported by StageSystem')
    if installation.get('velocity_from_encoder', True) is False:
        value = installation.get('velocity_mps_per_raw_unit')
        if not isinstance(value, (int, float)) or not math.isfinite(value) or value == 0:
            raise ValueError('review signed raw velocity conversion')
    # Optional unknown conversion/bounds remain unknown in durable metadata.
    # Required SI conversions above must be finite; no unknown becomes a scale.
    def metadata(value):
        if isinstance(value, dict):
            return {k: metadata(v) for k, v in value.items()}
        if isinstance(value, list):
            return [metadata(v) for v in value]
        return None if isinstance(value, float) and not math.isfinite(value) else value
    return {'profile_id': settings['calibration_profile_id'], 'coordinate_convention': settings['coordinate_convention'],
            'force_convention': settings['force_convention'], 'profile_sha256': hashes,
            'installation': metadata(installation), 'controller_configuration': documents['controllers_file'],
            'hardware_configuration': documents['hardware_file']}


def active_stage(response):
    components = [c for c in response.component if c.name == 'StageSystem']
    if len(components) != 1 or components[0].state.label != 'active':
        raise ValueError('StageSystem must be active (explicit Prepare hardware required)')
    stage = components[0]
    if stage.class_type != 'zfc_ethercat_hardware/EthercatHardware':
        raise ValueError('StageSystem is not the physical EthercatHardware plugin')
    available = {i.name for i in stage.state_interfaces if i.is_available}
    if not {'carriage/position', 'carriage/velocity', 'load_cell/force.x', 'load_cell/force.y', 'load_cell/force.z'} <= available:
        raise ValueError('StageSystem SI feedback interfaces unavailable')
    commands = [i for i in stage.command_interfaces if i.name == 'carriage/position' and i.is_available]
    if len(commands) != 1:
        raise ValueError('StageSystem position command interface unavailable')
    return stage
