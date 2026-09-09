# Sprint 3 Data Flow

## Data Flow Summary

Sprint 3 establishes the complete embedded-to-Linux communication pipeline using deterministic dummy telemetry generated on the STM32H743ZI running FreeRTOS.

Instead of real IMU measurements, mathematically generated telemetry packets are transferred over SPI to the NVIDIA Jetson Nano, validating the entire communication stack before integrating physical sensors in later sprints.

---

## System Data Flow

1. STM32H743ZI boots.
2. HAL initializes clocks, GPIO, UART, SPI and FreeRTOS.
3. FreeRTOS starts the telemetry task.
4. Producer module generates deterministic dummy telemetry.
5. Packet module packs telemetry into a fixed binary packet.
6. Transport module prepares the SPI transmit buffer.
7. STM32 asserts the DATA_READY GPIO line.
8. NVIDIA Jetson Nano detects the GPIO interrupt.
9. Linux kernel driver schedules bottom-half work.
10. Workqueue performs the SPI transaction.
11. Received packet is validated.
12. Packet is pushed into a kernel kfifo.
13. User-space application reads from /dev/telem0.
14. Packet is decoded, logged and prepared for visualization.

---

## Packet Example

SEQ=12
TS_US=123456
AX=-345
AY=111
AZ=1023
GX=10
GY=11
GZ=-3

---

## Packet Characteristics

- Fixed packet size
- Binary protocol
- Shared ABI between firmware and Linux
- Sequence-numbered
- Timestamped
- Deterministic dummy telemetry
- Machine readable
- Low latency
- Future compatible with MPU-9250 sensor data

---

## Sprint 3 Objective

Sprint 3 validates the complete communication path without introducing sensor-side uncertainty.

Only after the Linux SPI bridge is proven stable will the dummy telemetry generator be replaced by MPU-9250 measurements in Sprint 5.
