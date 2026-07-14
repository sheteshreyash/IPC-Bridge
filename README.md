# IPC Bridge Project

A modular Embedded Linux IPC project demonstrating deterministic telemetry transfer between an STM32H743ZI microcontroller and an NVIDIA Jetson Nano using SPI, GPIO interrupts and a custom Linux kernel driver.

---

## Current Sprint

Sprint 3

Embedded Linux IPC Infrastructure using Dummy Telemetry

---

## Hardware

STM32 NUCLEO-H743ZI
MPU-9250 (planned for Sprint 5)
NVIDIA Jetson Nano P3450 4GB
Windows 11
Ubuntu 22.04 LTS
STM32CubeIDE

---

## Current Status

✔ Sprint 1 completed
UART dummy telemetry

✔ Sprint 2 completed
FreeRTOS integration

🚧 Sprint 3 in progress
Embedded Linux IPC infrastructure

---

## Sprint Roadmap

- Sprint 1
Dummy telemetry over UART

- Sprint 2
FreeRTOS scheduler

- Sprint 3
Embedded Linux IPC infrastructure using dummy telemetry

- Sprint 4
Bare metal MPU-9250 driver and SPI integration with RTOS

- Sprint 5
Replace dummy telemetry with RTOS with MPU-9250 sensor data

- Sprint 6
Visualization, benchmarking and optimization

---

## Repository Structure

- docs/
Project documentation

- firmware/
STM32 firmware

- kernel/
Linux kernel module

- shared/
Shared communication protocol

- user/
User-space applications

- scripts/
Build scripts

hardware/
Hardware documentation

benchmarks/
Performance measurements

.github/
CI workflows

---

## Project Goals

- Modular firmware architecture
- Embedded Linux kernel programming
- SPI-based IPC
- Interrupt-driven communication
- Shared firmware/Linux ABI
- Production-style project organization

---

## Telemetry Status

Current firmware still transmits deterministic dummy telemetry.
This allows the entire Linux communication pipeline to be validated before introducing real IMU data.

---

## License

MIT
