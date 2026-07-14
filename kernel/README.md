# Sprint 3 Linux Kernel Driver (Jetson Nano)

This directory contains the Linux kernel driver for the IPC Bridge project.

## Current target hardware

- NVIDIA Jetson Nano Developer Kit (P3450 4GB)
- STM32 NUCLEO-H743ZI
- SPI Master (Jetson)
- SPI Slave (STM32)

---

## Current Sprint

Sprint 3 — Dummy Telemetry IPC Bridge

### Implemented

- SPI driver registration
- misc character device (/dev/telem0)
- IRQ skeleton
- Workqueue
- kfifo
- userspace ABI
- polling support

### Pending

- Jetson Device Tree
- Jetson SPI bring-up
- Real hardware validation
