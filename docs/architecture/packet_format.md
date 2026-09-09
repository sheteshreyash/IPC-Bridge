# Sprint 3 Packet Format

## Current packet type

Fixed-format telemetry packet for IPC bridge validation

## Fields

- SEQ
- TS_US
- AX
- AY
- AZ
- GX
- GY
- GZ

## Example packet

SEQ=0,TS_US=0,AX=-1000,AY=-1000,AZ=1000,GX=-250,GY=-250,GZ=-250

## Notes

- Sprint 3 still uses dummy telemetry
- The packet is structured so it can be fetched over SPI and later extended for CRC and binary framing
- UART debug output remains available, but the IPC path itself is packet-based

## Future evolution

Later sprints may convert this into:

- fixed-size binary packet
- CRC-protected payload
- sequence gap detection
- timestamp synchronization fields
- Linux-readable IPC frame
- sensor-specific metadata
