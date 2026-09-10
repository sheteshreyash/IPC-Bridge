# Latency Reports

## Purpose

This file stores timing and performance measurements for the IPC Bridge.

Sprint 3 established the baseline using deterministic dummy telemetry.

Sprint 4 introduces real MPU-9250 data.

---

## Metrics

Capture:

- sensor acquisition interval
- telemetry packet generation interval
- DATA_READY assertion timing
- DATA_READY to Jetson IRQ latency
- IRQ to workqueue scheduling latency
- SPI transaction duration
- kernel packet processing time
- userspace wakeup latency
- end-to-end packet delivery latency
- packet loss
- sequence gaps
- jitter

---

## Sprint 3 Baseline

Record:

- dummy telemetry rate
- packet rate
- packet period
- sequence continuity
- timestamp delta
- FIFO behavior

---

## Sprint 4 Sensor Baseline

Record:

- MPU-9250 configured sample rate
- actual sensor acquisition interval
- telemetry packet rate
- packet loss
- sequence gaps
- timestamp variation
- CPU load
- memory usage

---

## Measurement Run Format

### Run ID

Example:

```text
S4-RUN-01
```
