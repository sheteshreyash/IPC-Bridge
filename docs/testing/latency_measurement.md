# Sprint 3 - System Latency & Determinism Measurement

## Objective

Measure the end-to-end jitter and packet loss of the IPC Bridge.

## Prerequisites

1. The `telem0_driver` is loaded.
2. The `telemetry_reader` C++ application is compiled.

## Test Procedure

1. Stop the STM32 (hit the reset button and hold it).
2. Start the `telemetry_reader` on the Pi and pipe the output to a file:
   `./telemetry_reader > capture.csv`
3. Release the STM32 reset button and let it run for exactly 60 seconds.
4. Stop the reader application (`Ctrl+C`).

## Analysis Metrics

### 1. Packet Loss (Sequence Tracking)

Open `capture.csv` and analyze the `SEQ=` column.

* Are there any missing numbers? (e.g., `SEQ=405` jumps to `SEQ=407`).
* A missing sequence number indicates the Pi's Workqueue was too slow, and the STM32 overwrote the data before the Pi could read it.

### 2. Jitter (Timestamp Delta)

Analyze the `TS_US=` column.

* The delta between each packet should be exactly `10000` (10ms).
* Variations in this delta represent the Jitter introduced by the FreeRTOS scheduler or the Linux Kernel's interrupt latency.
