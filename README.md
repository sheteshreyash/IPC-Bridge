
# IPC Bridge Project

A modular Embedded Linux IPC project demonstrating deterministic telemetry transfer between an STM32H743ZI microcontroller and an NVIDIA Jetson Nano using SPI, GPIO interrupts and a custom Linux kernel driver.

---

## Current Sprint

### Sprint 3 — Embedded Linux IPC Infrastructure Using Dummy Telemetry

### Status

#### Sprint 3 Complete

The first end-to-end embedded-to-Linux telemetry pipeline has been successfully validated using deterministic dummy telemetry.

---

## Hardware

- STM32 NUCLEO-H743ZI
- NVIDIA Jetson Nano Developer Kit P3450 4GB
- MPU-9250 GY-9250 9-Axis Sensor Module — planned for later sensor integration
- Windows 11 development environment
- Ubuntu 22.04 LTS development environment
- STM32CubeIDE

### Jetson Nano Platform

- Custom Jetson Nano Linux image
- L4T R32.7.6
- Ubuntu 18.04.6 LTS
- Linux 4.9.337-tegra
- AArch64

---

## Current Status

### Sprint 1 — Complete

#### Dummy telemetry over UART

The STM32 generated deterministic telemetry and transmitted it through UART.

### Sprint 2 — Complete

#### FreeRTOS integration

Telemetry generation was moved into a FreeRTOS task environment with periodic scheduling and RTOS-based task execution.

### Sprint 3 — Complete

#### Embedded Linux IPC infrastructure

The STM32 dummy telemetry now travels through:

```text
STM32 FreeRTOS
      ↓
36-byte telemetry packet
      ↓
SPI slave
      ↓
DATA_READY GPIO
      ↓
Jetson GPIO interrupt
      ↓
Linux kernel workqueue
      ↓
SPI master transaction
      ↓
Packet validation
      ↓
kfifo
      ↓
/dev/telem0
      ↓
User-space telemetry reader
```
