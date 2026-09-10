# Sprint 4 Packet Format

## Current Packet Type

Sprint 4 continues to use the fixed-format telemetry packet established during Sprint 3.

The packet ABI is intentionally preserved while the data source changes from dummy telemetry to real MPU-9250 measurements.

---

## Current Structure

The shared packet contains:

```text
magic
seq
ts_us
ax
ay
az
gx
gy
gz
```
