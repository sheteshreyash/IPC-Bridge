# Sprint 1 Timing Model

## Purpose

This document defines the timing behavior of dummy telemetry transmission in Sprint 1.

## Current timing

- Telemetry generated periodically in the main loop
- Each frame is sent using HAL_UART_Transmit
- Delay used between frames: HAL_Delay(100) or HAL_Delay(250)

## Notes

Sprint 1 does not require hard real-time timing.
The purpose is only to validate:

- stable UART output
- clean formatting
- predictable message flow

## Expected behavior

- one message every fixed interval
- sequence counter increases monotonically
- values change every frame
- no terminal corruption
- no missing line breaks

## Why this matters later

This timing baseline will later help compare:

- FreeRTOS timing
- DMA-based timing
- real sensor timing
- Linux bridge latency
