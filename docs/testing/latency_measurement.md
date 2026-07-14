# Sprint 3 - Latency Measurement

## Purpose

Measure the deterministic behavior of the IPC bridge using dummy telemetry.

---

## Objective

Measure

- packet period
- interrupt latency
- packet loss
- jitter

between STM32 and Jetson Nano.

---

## Test Procedure

1. Start telemetry reader

```bash
./telemetry_reader > capture.csv
```

1. Allow the system to run for 60 seconds

1. Stop

```bash
CTRL+C
```

1. Metrics

Packet Loss

1. Verify

```bash
SEQ
```

---

## increments without gaps

Example

401
402
403
404

---

## No missing values

- Timing
Check

```bash
TS_US
```

difference.
Expected

10000 us

for a

100 Hz

producer.

Jitter

Measure

ΔTS_US

---

## Acceptable variation depends on

- FreeRTOS scheduling
- Linux scheduling
- SPI latency

---

## Pass Criteria

- No packet loss
- Stable packet timing
- Consistent interrupt response
- No driver errors
- Failure Cases
- Missing sequence numbers
- Variable timestamps
- Buffer overflow
- Driver timeout
- Lost interrupts

---

## Future

Sprint 6 extends this with

- throughput benchmarking
- histogram generation
- latency plots
