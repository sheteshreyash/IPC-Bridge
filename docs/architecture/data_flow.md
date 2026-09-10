# Sprint 4 Data Flow

## Data Flow Summary

Sprint 4 replaces the deterministic dummy telemetry source used in Sprint 3 with real measurements obtained from the MPU-9250 sensor.

The existing STM32-to-Jetson IPC architecture remains unchanged wherever possible.

The primary objective is to introduce real sensor acquisition without simultaneously redesigning the Linux transport path.

---

## System Data Flow

1. STM32H743ZI boots.
2. STM32 HAL initializes clocks, GPIO, UART, sensor bus, SPI and FreeRTOS.
3. MPU-9250 is initialized.
4. STM32 verifies the sensor identity using the WHO_AM_I register.
5. Sensor configuration is applied.
6. FreeRTOS sensor task periodically reads sensor registers.
7. Raw accelerometer and gyroscope measurements are captured.
8. Sensor values are stored in the STM32 sensor data structure.
9. Telemetry producer consumes the latest valid sensor sample.
10. Packet builder places the real sensor values into `telem0_packet_t`.
11. Transport prepares the SPI transmit buffer.
12. STM32 asserts the DATA_READY GPIO line.
13. Jetson Nano detects the GPIO interrupt.
14. Linux kernel driver schedules deferred work.
15. Kernel workqueue performs the SPI transaction.
16. Received packet is validated using the packet MAGIC value.
17. Valid packet is inserted into the kernel kfifo.
18. `/dev/telem0` becomes readable.
19. User-space telemetry reader reads and decodes the packet.
20. Real accelerometer and gyroscope values are printed and logged.

---

## Sensor Path

```text
MPU-9250
    |
    v
STM32 Sensor Driver
    |
    v
Raw Sensor Sample
    |
    v
FreeRTOS Sensor Task
    |
    v
Telemetry Producer
```
