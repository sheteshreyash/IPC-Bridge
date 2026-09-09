# Sprint 4 — Real Telemetry End-to-End Validation

## Objective

Verify that real MPU-9250 accelerometer and gyroscope measurements reach Jetson userspace through the existing Sprint 3 IPC architecture.

## Data Path

```text
MPU-9250
    ↓
STM32
    ↓
FreeRTOS
    ↓
Telemetry Packet
    ↓
SPI
    ↓
Jetson IRQ
    ↓
Kernel Driver
    ↓
kfifo
    ↓
/dev/telem0
    ↓
telemetry_reader
```
