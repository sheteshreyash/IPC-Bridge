# Sprint 3 System Overview

## Goal

Sprint 3 transforms the project from a standalone embedded firmware application into a heterogeneous Embedded Linux IPC system.

The STM32H743ZI acts as a deterministic real-time telemetry producer, while the NVIDIA Jetson Nano acts as the Embedded Linux consumer.

Real IMU measurements are intentionally postponed until Sprint 5. Sprint 3 focuses entirely on validating the communication infrastructure using deterministic dummy telemetry.

---

## Current Scope

STM32 Side

- FreeRTOS scheduler
- Producer module
- Packet builder
- SPI slave interface
- DATA_READY GPIO signaling
- UART debug output

Jetson Nano Side

- Linux SPI master
- GPIO interrupt handling
- Linux kernel driver
- Workqueue processing
- kfifo buffering
- Character device (/dev/telem0)
- User-space telemetry reader

---

## Current Hardware

- STM32 NUCLEO-H743ZI
- NVIDIA Jetson Nano P3450 (4GB)
- MPU-9250 IMU module (reserved for Sprint 5)
- USB Type-A to Micro-USB cable
- Female-to-female jumper wires
- Windows 11
- Ubuntu 22.04 LTS
- STM32CubeIDE
- Visual Studio Code
- Linux kernel build environment

---

## High-Level Architecture

STM32H743ZI
↓
FreeRTOS
↓
Telemetry Producer
↓
Packet Builder
↓
SPI Slave + DATA_READY GPIO
↓
NVIDIA Jetson Nano
↓
Linux SPI Driver
↓
kfifo
↓
/dev/telem0
↓
User-space Telemetry Reader

---

## Sprint 3 Objectives

Sprint 3 validates

- Embedded-to-Linux IPC
- SPI communication
- GPIO interrupt synchronization
- Linux kernel driver framework
- Character device interface
- User-space communication
- Deterministic packet transport

---

## Not Included

- MPU-9250 acquisition
- Sensor fusion
- DMA optimization
- Performance benchmarking
- Live visualization
- Production latency optimization

---

## Expected Outcome

A fully functional communication infrastructure capable of transferring deterministic telemetry packets from the STM32 to the Jetson Nano through an interrupt-driven Linux kernel architecture.

Only after this infrastructure is validated will dummy telemetry be replaced with real MPU-9250 measurements.
