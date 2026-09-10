# Sprint 4 IPC Design

## Purpose

This document defines the IPC architecture used after replacing Sprint 3 dummy telemetry with real MPU-9250 measurements.

The Linux-side IPC design established in Sprint 3 remains unchanged.

Sprint 4 changes the telemetry source rather than redesigning the transport.

---

## IPC Medium

### Primary transport

- SPI

### Synchronization

- DATA_READY GPIO interrupt

### Debug Interface

- UART on STM32

---

## System Roles

### STM32H743ZI

The STM32 is responsible for:

- MPU-9250 communication
- sensor initialization
- sensor sampling
- FreeRTOS scheduling
- telemetry packet creation
- SPI slave transmission
- DATA_READY signaling
- optional UART diagnostics

### MPU-9250

The MPU-9250 provides:

- 3-axis accelerometer
- 3-axis gyroscope
- 3-axis magnetometer

The initial Sprint 4 telemetry ABI uses the accelerometer and gyroscope fields already present in `telem0_packet_t`.

### Jetson Nano

The Jetson remains responsible for:

- SPI master operation
- GPIO interrupt reception
- Linux kernel driver execution
- packet buffering
- userspace access

### Linux Kernel Driver

The existing `telem0_driver`:

- receives DATA_READY interrupts
- schedules workqueue processing
- performs SPI transactions
- validates packet MAGIC
- buffers packets in kfifo
- exposes `/dev/telem0`

### User-space Application

The telemetry reader:

- opens `/dev/telem0`
- waits using `poll()`
- reads telemetry packets
- validates the packet ABI
- prints and logs real sensor values

---

## Sensor Interface

The MPU-9250 interface is treated as a separate subsystem from the STM32-to-Jetson SPI bridge.

The sensor bus and exact STM32 GPIO assignments must be kept consistent with the final STM32CubeIDE project configuration.

The SPI1 peripheral used for the Jetson bridge must remain dedicated to the IPC path.

---

## Why the separation matters

Two independent communication paths are intentionally maintained:

```text
MPU-9250
    |
    | Sensor bus
    v
STM32
    |
    | SPI1 IPC
    v
Jetson Nano
```
