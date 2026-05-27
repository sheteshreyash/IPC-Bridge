# Sprint 3 Latency Reports

## Purpose

This file will store latency measurements and summary notes for the dummy-data IPC bridge.

## Metrics to capture

- STM32 packet generation interval
- DATA_READY to Pi interrupt latency
- SPI transaction completion time
- kernel driver processing time
- user-space read latency
- end-to-end latency from packet ready to user-space availability

## Report format

For each run, capture:

- date and time
- firmware version or git commit
- kernel driver version or git commit
- packet rate
- load conditions
- median latency
- min latency
- max latency
- jitter / variation
- packet loss count

## Example sections

### Run 1

- idle system
- no extra CPU load
- dummy telemetry only

### Run 2

- CPU stress on Pi
- dummy telemetry only

### Run 3

- longer run
- buffer and loss analysis

## Notes

Keep raw logs in a separate folder and summarize only the important conclusions here.
