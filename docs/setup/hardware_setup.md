# Sprint 4 Hardware Setup

## Purpose

This document defines the physical hardware connections used during Sprint 4.

Sprint 4 introduces the MPU-9250 GY-9250 IMU as the real telemetry source while preserving the STM32-to-Jetson Nano IPC interface validated during Sprint 3.

---

## System Architecture

The hardware system contains three major components:

```text
MPU-9250
    |
    | Sensor interface
    v
STM32 NUCLEO-H743ZI
    |
    | SPI + DATA_READY
    v
NVIDIA Jetson Nano
```
