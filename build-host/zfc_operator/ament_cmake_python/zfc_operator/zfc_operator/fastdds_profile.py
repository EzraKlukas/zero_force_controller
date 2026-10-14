"""Scoped Fast DDS 2.x UDP interface allowlist; never changes middleware."""
import argparse
import ipaddress
from pathlib import Path
import socket
from .vendor_version import installed_version


def profile(version, local):
    ip = ipaddress.IPv4Address(local)
    if ip.is_unspecified or ip.is_multicast or str(ip) == '255.255.255.255':
        raise ValueError('select an explicit local unicast address')
    if not version.startswith('2.'):
        raise ValueError('review installed Fast DDS schema for '+version)
    return f'''<?xml version="1.0"?>
<profiles xmlns="http://www.eprosima.com/XMLSchemas/fastRTPS_Profiles">
  <transport_descriptors><transport_descriptor><transport_id>zfc_session_udp</transport_id><type>UDPv4</type>
    <interfaceWhiteList><address>127.0.0.1</address><address>{local}</address></interfaceWhiteList>
  </transport_descriptor></transport_descriptors>
  <participant profile_name="zfc_session" is_default_profile="true"><rtps>
    <userTransports><transport_id>zfc_session_udp</transport_id></userTransports><useBuiltinTransports>false</useBuiltinTransports>
  </rtps></participant>
</profiles>
'''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--local-address', required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    try:
        version = installed_version('fastrtps')
        document = profile(version, args.local_address)
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
            sock.bind((args.local_address, 0))
        with args.output.open('x') as stream:
            stream.write(document)
    except Exception as error:
        parser.exit(1, str(error)+'\n')
    print(f'Generated for installed Fast DDS {version}: {args.output}; validate with bidirectional network_probe on both computers.')
