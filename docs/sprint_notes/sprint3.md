# Sprint 3 — Embedded Linux IPC Infrastructure

## Goal

Develop the complete embedded-to-Linux communication infrastructure between the STM32H743ZI and the NVIDIA Jetson Nano using deterministic dummy telemetry.

---

## Motivation

Sprint 3 marks the transition from standalone embedded firmware into a heterogeneous embedded Linux system.

Instead of validating only firmware functionality, this sprint validates the complete communication pipeline from firmware through the Linux kernel and into user space.

---

## Included Scope

STM32

- FreeRTOS scheduler
- Producer module
- Packet module
- Transport module
- SPI Slave
- DATA_READY GPIO

Linux

- Device Tree Overlay
- SPI driver scaffold
- GPIO interrupt framework
- Workqueue
- Character device
- User-space reader
- Shared protocol definitions

Documentation

- Architecture
- Packet format
- Data flow
- IPC design
- Testing
- Setup guides

---

## Not Included

- MPU-9250 sensor acquisition
- Sensor calibration
- DMA optimization
- Real-time visualization
- Performance tuning
- Packet compression
- Advanced error recovery

---

## High-Level Architecture

STM32H743ZI
↓
FreeRTOS
↓
Producer
↓
Packet Builder
↓
Transport
↓
SPI Slave
↓
DATA_READY
↓
Jetson Nano
↓
Linux Kernel Driver
↓
kfifo
↓
/dev/telem0
↓
User-space Reader

---

## Sprint 3 Validation

Firmware
✔ Modular architecture
✔ FreeRTOS integration
✔ Dummy telemetry generation
✔ SPI packet preparation

Linux
✔ Kernel module compilation
✔ Device Tree Overlay
✔ User-space application
✔ Shared protocol

Repository
✔ Documentation
✔ Build scripts
✔ Project organization

---

## Expected Outcome

At the end of Sprint 3, the complete software infrastructure will be ready.
The only remaining dependency will be connecting the Jetson Nano hardware and validating live SPI communication.
Once validated, the dummy telemetry generator will be replaced by MPU-9250 sensor data during Sprint 5.
