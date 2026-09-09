# Release v0.3 — Sprint 3 Complete

## Release Summary

Sprint 3 completes the first end-to-end Embedded Linux IPC pipeline for the IPC Bridge project.

The STM32 NUCLEO-H743ZI generates deterministic dummy telemetry under FreeRTOS and exposes the telemetry to an NVIDIA Jetson Nano through an SPI-based IPC bridge.

The Jetson Nano receives a DATA_READY interrupt from the STM32, performs the SPI transaction through a custom Linux kernel driver, validates the telemetry packet, buffers it using a kernel kfifo, and exposes the data through `/dev/telem0` to a user-space telemetry reader.

This release establishes the complete embedded-to-Linux communication path before introducing real IMU sensor data.

---

## Release Version

### v0.3

### Sprint

Sprint 3 — Embedded Linux IPC Infrastructure Using Dummy Telemetry

### Status

### Completed

---

## Objectives

Sprint 3 was designed to move the project from UART-only telemetry validation to a heterogeneous embedded-to-Linux IPC architecture.

The primary objectives were:

- establish SPI communication between STM32 and Jetson Nano
- implement DATA_READY GPIO notification
- implement interrupt-driven Linux-side reception
- move SPI transactions out of hard IRQ context
- introduce kernel-side packet buffering
- expose telemetry through a character device
- provide a user-space telemetry reader
- validate the complete pipeline using deterministic dummy telemetry

---

## Hardware Platform

### STM32

- STM32 NUCLEO-H743ZI
- STM32H743ZI
- FreeRTOS-based telemetry producer
- SPI1 configured as SPI slave
- USART3 retained as debug output
- DATA_READY GPIO used as interrupt notification

### Jetson Nano

- NVIDIA Jetson Nano Developer Kit P3450 4GB
- Custom Jetson Nano Linux image
- L4T R32.7.6
- Ubuntu 18.04.6 LTS
- Linux 4.9.337-tegra
- AArch64

### Additional Hardware

- Ethernet connection for headless Jetson access
- SPI jumper connections
- GPIO interrupt connection
- Common ground connection

---

## Physical IPC Connections

The validated Sprint 3 interface is:

| Jetson Nano | Function | STM32 NUCLEO-H743ZI |
| --- | --- | --- |
| Physical Pin 19 | SPI MOSI | PA7 / SPI1_MOSI |
| Physical Pin 21 | SPI MISO | PA6 / SPI1_MISO |
| Physical Pin 23 | SPI SCLK | PA5 / SPI1_SCK |
| Physical Pin 24 | SPI CS0 | PA4 / SPI1_NSS |
| Physical Pin 31 | DATA_READY | PB1 |
| Physical Pin 20 | GND | GND |

The Jetson SPI interface is exposed through the Jetson 40-pin header.

Linux maps the active controller to:

```text
7000d400.spi
    |
    +-- spi0
          |
          +-- spi0.0
