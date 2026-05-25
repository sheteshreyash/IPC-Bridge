# Sprint 1 Packet Format

## Current packet type

Text packet for UART console validation

## Fields

- SEQ
- UPTIME_MS
- AX
- AY
- AZ
- GX
- GY
- GZ

## Example packet

SEQ=0,UPTIME_MS=0,AX=-1000mg,AY=-1000mg,AZ=1000mg,GX=-2000mdps,GY=-2000mdps,GZ=-2000mdps

## Notes

- Sprint 1 packet is human-readable
- Binary packets, CRC, and alignment will come later
- This format is intentionally simple for bring-up and debugging

## Future evolution

Later sprints may convert this into:

- fixed-size binary packet
- CRC-protected payload
- timestamped sensor frame
- Linux-readable IPC frame
