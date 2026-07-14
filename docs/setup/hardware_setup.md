# Sprint 3 Hardware Setup

## Purpose

This document defines the physical hardware connections between the STM32H743ZI and the NVIDIA Jetson Nano.

---

## Design Summary

STM32

- SPI Slave
- DATA_READY GPIO Producer
- UART Debug

Jetson Nano

- SPI Master
- GPIO Interrupt Consumer
- Linux Kernel Driver

---

## Hardware

- STM32 NUCLEO-H743ZI
- NVIDIA Jetson Nano P3450 (4GB)
- MPU-9250 (Sprint 5)
- Jumper wires
- USB cables

---

## Required Signals

- SPI_SCK
- SPI_MOSI
- SPI_MISO
- SPI_CS
- DATA_READY
- GND

---

## Validation Checklist

- Common Ground
- 3.3V Logic
- SPI Clock
- Chip Select
- GPIO Interrupt
- UART Debug

---

## Wiring

⚠ Final Jetson Nano GPIO numbering and header pin mapping will be documented after Jetson bring-up.

Sprint 3 intentionally keeps the hardware abstraction independent from Jetson-specific pin numbers until the platform is configured.

---

## Important Notes

- Never connect 5V logic.
- Both STM32H7 and Jetson Nano operate at 3.3V.
- Verify continuity before power-up.
- Verify SPI mode (CPOL=0, CPHA=0).
