"""Read the selected installation's vendor metadata, never assume a version.

Upstream middleware packages are often plain CMake and have no ament index entry.
Prefer sourced-prefix CMake/XML metadata, then Ubuntu's installed ROS package.
"""
import os
from pathlib import Path
import re
import subprocess
import xml.etree.ElementTree as ET


def installed_version(vendor):
    if vendor not in ('fastrtps', 'cyclonedds'):
        raise ValueError('unsupported vendor')
    prefixes = list(dict.fromkeys(os.environ.get('CMAKE_PREFIX_PATH', '').split(':')+
                                 os.environ.get('AMENT_PREFIX_PATH', '').split(':')))
    for prefix in prefixes:
        if not prefix:
            continue
        share = Path(prefix)/'share'
        xml = share/vendor/'package.xml'
        if xml.is_file():
            return ET.parse(xml).getroot().findtext('version')
        candidates = (share/'fastrtps/cmake/fastrtps-config-version.cmake',) if vendor == 'fastrtps' else (
            share/'CycloneDDS/cmake/CycloneDDSConfigVersion.cmake',
            Path(prefix)/'lib/cmake/CycloneDDS/CycloneDDSConfigVersion.cmake',
            share/'cyclonedds/cmake/CycloneDDSConfigVersion.cmake')
        for candidate in candidates:
            if candidate.is_file():
                match = re.search(r'set\(PACKAGE_VERSION\s+"?([0-9]+\.[0-9]+\.[0-9]+)', candidate.read_text())
                if match:
                    return match.group(1)
    result = subprocess.run(['dpkg-query', '-W', '-f=${Status} ${Version}', 'ros-humble-'+vendor],
                            check=False, capture_output=True, text=True)
    match = re.fullmatch(r'install ok installed ([0-9]+\.[0-9]+\.[0-9]+).*', result.stdout.strip())
    if result.returncode == 0 and match:
        return match.group(1)
    raise ValueError('cannot determine installed '+vendor+' version; inspect the actual sourced vendor installation')
