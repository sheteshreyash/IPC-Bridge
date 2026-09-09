# Sprint 4 Timing Model

## Purpose

This document defines the timing behavior after replacing the Sprint 3 dummy telemetry source with real MPU-9250 measurements.

The first objective is stable sensor acquisition and transport rather than minimum possible latency.

---

## Timing Flow

1. FreeRTOS schedules the sensor acquisition task.
2. The STM32 reads the configured MPU-9250 sensor registers.
3. The sensor sample is stored.
4. The telemetry producer creates a packet from the latest valid sample.
5. The packet is prepared for SPI transmission.
6. DATA_READY is asserted.
7. Jetson GPIO interrupt occurs.
8. Linux hard IRQ schedules workqueue processing.
9. Workqueue performs the SPI transaction.
10. Packet is validated.
11. Packet enters kfifo.
12. Userspace is awakened.
13. Userspace reads and logs the sensor values.

---

## Initial Target

The exact sensor acquisition rate must be determined by the final MPU-9250 configuration.

The Sprint 3 100 Hz IPC cadence may be retained initially so that the comparison against the dummy-data system remains straightforward.

---

## Timing Components

```text
Sensor acquisition
        +
FreeRTOS scheduling
        +
Packet construction
        +
DATA_READY assertion
        +
GPIO IRQ latency
        +
SPI transfer
        +
Kernel buffering
        +
Userspace wakeup
```
