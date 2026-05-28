# Sprint 3 Timing Model

## Purpose

This document defines the timing behavior of the dummy-data IPC bridge.

## Current timing

- Telemetry generation is periodic under FreeRTOS
- A fixed-rate telemetry task produces frames
- DATA_READY is asserted when a packet is available
- Raspberry Pi responds to the interrupt and fetches the frame
- User-space reads the data from the kernel device

## Notes

Sprint 3 is not the final low-latency optimized version.
The purpose is to prove that timing remains stable through:

- RTOS scheduling
- hardware interrupt notification
- SPI transfer
- kernel buffering
- user-space readout

## Expected behavior

- periodic packet generation
- deterministic packet availability
- predictable interrupt behavior
- stable end-to-end flow
- no lost packets in normal operation

## Why this matters later

This timing baseline becomes the reference for:

- real sensor timing
- DMA-based transfer tuning
- kernel latency profiling
- end-to-end latency measurement
