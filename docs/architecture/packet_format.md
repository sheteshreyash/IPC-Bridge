# Sprint 3 Packet Format

## Current packet type

Fixed-size telemetry packet for IPC bridge validation

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

- Sprint 3 moves from purely terminal-friendly text output to a structured IPC packet mindset
- The packet is still based on dummy telemetry
- The packet must be simple enough to validate through UART and later SPI
- CRC can be introduced in later sprint refinement if needed

## Future evolution

Later sprints may convert this into:

- fixed-size binary packet
- CRC-protected payload
- sequence gap detection
- timestamp synchronization fields
- Linux-readable IPC frame
- sensor-specific metadata
