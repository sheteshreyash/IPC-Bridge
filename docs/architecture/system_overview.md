# Sprint 3 System Overview

## Goal

Sprint 3 turns the project into a real Linux IPC bridge using the STM32 as the real-time producer and the Raspberry Pi as the Linux consumer.

## Current scope

- STM32 firmware still generates dummy telemetry
- FreeRTOS continues to schedule the telemetry task
- STM32 packages data into a fixed frame
- STM32 signals the Raspberry Pi using a GPIO data-ready line
- Raspberry Pi receives data through a Linux kernel driver
- User-space daemon reads the data and prepares it for logging/visualization

## Current hardware

- STM32 NUCLEO-H743ZI
- Raspberry Pi 4
- USB cable for STM32 flashing and debug
- Jumper wires for SPI and GPIO interrupt connection
- Laptop running Windows 11 + Ubuntu 22.04 dual boot
- Serial terminal software for debug output
- Linux tools for kernel module testing and data capture

## High-level architecture

STM32 FreeRTOS telemetry source
    -> SPI + DATA_READY GPIO
Raspberry Pi Linux kernel driver
    -> /dev/stm32_imu character device
User-space daemon
    -> CSV logging / latency reporting / visualization

## Why this sprint exists

This sprint validates:

- STM32 to Raspberry Pi physical IPC
- Linux kernel driver integration
- interrupt-driven receive flow
- kernel buffer usage
- user-space data consumption
- low-latency pipeline behavior

## Not included yet

- real sensor board
- DMA-based real sensor acquisition
- final packet optimization
- production-grade error recovery
- advanced visualization polish

## Expected outcome

A working dummy-data IPC bridge from STM32 to Raspberry Pi with measured data movement through the Linux stack.
