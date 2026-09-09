# Sprint 3 IPC Design

## Purpose

This document defines the communication architecture between the STM32H743ZI firmware and the NVIDIA Jetson Nano Linux system.

Sprint 3 focuses on validating the communication infrastructure using deterministic dummy telemetry.

---

## IPC Medium

Primary transport

- SPI
Synchronization

- DATA_READY GPIO interrupt
Debug Interface

- UART (STM32 only)

---

## System Roles

STM32H743ZI

- Real-time telemetry producer
- SPI Slave
- FreeRTOS scheduler
- Packet generator

Jetson Nano

- SPI Master
- Embedded Linux Host

Linux Kernel Driver

- Handles GPIO interrupts
- Schedules workqueue
- Reads SPI packets
- Buffers packets using kfifo
- Exposes /dev/telem0

User-space Application

- Reads packets
- Decodes telemetry
- Logs packets
- Future visualization interface

---

## Why SPI?

SPI was selected because it provides

- deterministic transfers
- full duplex communication
- low software overhead
- excellent Linux kernel support
- high throughput
- simple hardware implementation

---

## Why DATA_READY?

An SPI slave cannot initiate communication.
The STM32 therefore asserts DATA_READY whenever a complete telemetry packet is available.
The Jetson Nano receives the GPIO interrupt and immediately schedules an SPI transaction.

---

## Future Expansion

- Sprint 5
Dummy telemetry
↓
MPU-9250 sensor measurements

- Sprint 6
User-space visualization
↓
Real-time plotting
↓
Performance optimization
