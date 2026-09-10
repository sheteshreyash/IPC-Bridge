# Sprint 4 — MPU-9250 Real Sensor Integration

## Goal

Replace the deterministic dummy telemetry source used in Sprint 3 with real measurements from the MPU-9250 GY-9250 sensor module while preserving the established STM32-to-Jetson IPC architecture.

---

## Why Sprint 4 Exists

Sprint 3 proved that the Linux IPC infrastructure works independently of physical sensor hardware.

The system successfully demonstrated:

```text
STM32 dummy telemetry
        ↓
SPI
        ↓
DATA_READY IRQ
        ↓
Jetson kernel driver
        ↓
kfifo
        ↓
/dev/telem0
        ↓
userspace
```
