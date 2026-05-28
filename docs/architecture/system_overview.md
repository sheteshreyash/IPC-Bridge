# Sprint 3 System Overview

## Goal

Sprint 3 turns the project into a real heterogeneous IPC system using the STM32 as the deterministic data producer and the Raspberry Pi as the Linux-side consumer.

## Current scope

- STM32 FreeRTOS telemetry generation continues
- STM32 formats dummy telemetry into a fixed packet
- STM32 acts as SPI slave
- Raspberry Pi acts as SPI master
- DATA_READY GPIO notifies the Pi that a packet is ready
- Pi kernel driver receives data and exposes it to user space
- UART remains available on STM32 as a debug path

## Current hardware

- STM32 NUCLEO-H743ZI
- Raspberry Pi 4
- USB cable for STM32 flashing and debug
- Jumper wires for SPI and GPIO interrupt connection
- Laptop running Windows 11 + Ubuntu 22.04 dual boot
- Serial terminal software for STM32 debug output
- Linux build tools for Pi kernel/user-space development

## High-level architecture

STM32 FreeRTOS telemetry source
    -> SPI slave + DATA_READY GPIO
Raspberry Pi Linux kernel driver
    -> /dev/telem0 character device
User-space daemon
    -> CSV logging / latency reporting / visualization

## Why this sprint exists

This sprint validates:

- STM32 to Raspberry Pi physical IPC
- interrupt-driven receive flow
- Linux kernel driver integration
- kernel buffering
- user-space data consumption
- low-latency pipeline behavior

## Not included yet

- real sensor board
- final DMA optimization
- advanced packet recovery
- full visualization polish
- production-ready performance tuning

## Expected outcome

A working dummy-data IPC bridge from STM32 to Raspberry Pi with clear separation between producer, transport, kernel, and user space.
