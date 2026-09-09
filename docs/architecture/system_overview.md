# Sprint 4 System Overview

## Goal

Sprint 4 introduces the MPU-9250 as the real telemetry source while preserving the Linux IPC architecture validated during Sprint 3.

The STM32H743ZI remains the real-time sensor and telemetry controller.

The NVIDIA Jetson Nano remains the Linux-side IPC consumer.

---

## Current Scope

### STM32 Side

- FreeRTOS
- MPU-9250 initialization
- sensor identity validation
- accelerometer acquisition
- gyroscope acquisition
- telemetry packet generation
- SPI slave IPC
- DATA_READY signaling
- UART diagnostics

### Jetson Nano Side

- SPI master
- GPIO interrupt handling
- Linux kernel driver
- workqueue processing
- kfifo buffering
- `/dev/telem0`
- userspace telemetry reader

---

## Hardware

- STM32 NUCLEO-H743ZI
- NVIDIA Jetson Nano P3450 4GB
- MPU-9250 GY-9250 module
- jumper wires
- STM32 ST-Link
- development workstation

---

## High-Level Architecture

```text
               MPU-9250
                   |
             Sensor Interface
                   |
                   v
           STM32H743ZI
                   |
             FreeRTOS
                   |
            Sensor Task
                   |
                   v
           Telemetry Producer
                   |
                   v
            Packet Builder
                   |
             SPI1 Slave
                   |
          DATA_READY GPIO
                   |
===================+====================
                   |
              Jetson Nano
                   |
             GPIO IRQ
                   |
           Linux Workqueue
                   |
              SPI Master
                   |
              Packet Check
                   |
                 kfifo
                   |
             /dev/telem0
                   |
           telemetry_reader
```
