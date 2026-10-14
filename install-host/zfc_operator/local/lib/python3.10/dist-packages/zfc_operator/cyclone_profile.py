"""Session-scoped unicast configuration for installed Humble Cyclone only."""
import argparse
import ipaddress
from pathlib import Path
import socket
from .vendor_version import installed_version


def profile(version, local, peer):
    for address in (local, peer):
        ip = ipaddress.IPv4Address(address)
        if ip.is_unspecified or ip.is_multicast or str(ip) == '255.255.255.255':
            raise ValueError('select explicit unicast addresses')
    if local == peer:
        raise ValueError('local and reciprocal peer must differ')
    if version.startswith(('0.9.', '0.10.')):
        interface = f'<Interfaces><NetworkInterface address="{local}"/></Interfaces>'
    else:
        raise ValueError('unsupported installed Cyclone version '+version+'; review its tagged schema')
    # Own selected address permits discovery between local processes too.
    return f'''<?xml version="1.0"?>
<CycloneDDS xmlns="https://cdds.io/config"><Domain Id="any">
  <General>{interface}<AllowMulticast>false</AllowMulticast></General>
  <Discovery><ParticipantIndex>auto</ParticipantIndex><MaxAutoParticipantIndex>32</MaxAutoParticipantIndex>
    <Peers><Peer Address="{local}"/><Peer Address="{peer}"/></Peers>
  </Discovery>
</Domain></CycloneDDS>
'''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--local-address', required=True)
    parser.add_argument('--peer-address', required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    try:
        version = installed_version('cyclonedds')
        document = profile(version, args.local_address, args.peer_address)
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as sock:
            sock.bind((args.local_address, 0)) # Verify THIS network namespace.
        with args.output.open('x') as stream:
            stream.write(document)
    except Exception as error:
        parser.exit(1, str(error)+'\n')
    print(f'Generated for installed Cyclone {version}: {args.output}. Validate parser and reciprocal topic/service preflight before hardware use.')
