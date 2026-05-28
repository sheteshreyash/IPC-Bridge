# Sprint 3 Hardware Setup

## Purpose

This document records the physical wiring between the STM32 NUCLEO-H743ZI and the Raspberry Pi 4 for the IPC bridge.

## Design summary

- STM32 is the SPI slave
- Raspberry Pi is the SPI master
- STM32 DATA_READY GPIO notifies the Pi that a new packet is ready
- UART remains available for STM32 debug output

## Signals to document

- SPI SCLK
- SPI MOSI
- SPI MISO
- SPI CS
- DATA_READY
- GND

## Notes

Fill in exact STM32 pins only after the CubeMX pinout is finalized.
Do not change pin assignments without updating this file and the wiring diagram.

## Validation

- continuity check
- correct logic level
- common ground verified
- SPI clock verified
- interrupt line verified
