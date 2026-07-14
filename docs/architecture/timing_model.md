# Sprint 3 Timing Model

## Purpose

This document describes the timing behavior of the Embedded Linux IPC pipeline implemented during Sprint 3.

The objective is deterministic packet generation rather than minimum latency.

---

## Timing Flow

1. FreeRTOS scheduler executes Telemetry Task every 10 ms.
2. Producer generates deterministic dummy telemetry.
3. Packet Builder constructs a binary telemetry packet.
4. Transport prepares the SPI transmit buffer.
5. STM32 asserts DATA_READY.
6. Jetson GPIO interrupt occurs.
7. Hard IRQ schedules Workqueue.
8. Workqueue performs SPI transaction.
9. Packet is validated.
10. Packet enters kfifo.
11. Userspace application wakes via poll().
12. Packet is logged.

---

## Current Timing Characteristics

Telemetry Rate
100 Hz

Packet Period
10 ms

Transport
SPI

Synchronization
GPIO Interrupt

Scheduling
FreeRTOS

Kernel
Interrupt-driven

Userspace
poll()/read()

---

## Sprint 3 Goals

Validate

- periodic telemetry generation
- deterministic packet timing
- interrupt latency
- SPI synchronization
- kernel buffering
- userspace delivery

---

## Future Timing Improvements

Sprint 5
Replace dummy telemetry with MPU-9250 acquisition.

Sprint 6

- DMA optimization
- latency profiling
- throughput benchmarking
- interrupt optimization
- visualization latency
