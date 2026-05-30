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

## Raspberry Pi 4 to STM32 NUCLEO-H743ZI Wiring Matrix

## Objective

Establish the physical SPI and Interrupt (EXTI) connections for the Sprint 3 IPC Bridge.

## The Wiring Table

**WARNING:** Both boards must be powered off before connecting jumper wires.

| Signal Name | STM32 Nucleo-144 (SPI1) | Raspberry Pi 4 (SPI0) | Pi Physical Header |
| :--- | :--- | :--- | :--- |
| **GND** | Any `GND` pin | `Ground` | **Pin 20** |
| **SPI_CS** | **PA4** (CN7 - A2) | `GPIO 8` (SPI0_CE0) | **Pin 24** |
| **SPI_CLK** | **PA5** (CN7 - D13) | `GPIO 11` (SPI0_SCLK) | **Pin 23** |
| **SPI_MISO** | **PA6** (CN7 - D12) | `GPIO 9` (SPI0_MISO) | **Pin 21** |
| **SPI_MOSI** | **PA7** (CN7 - D11) | `GPIO 10` (SPI0_MOSI) | **Pin 19** |
| **DATA_READY** | **PC7** (CN7 - Pin 19) | `GPIO 25` | **Pin 22** |

## Critical Notes

1. **Common Ground:** The `GND` wire is mandatory. Without it, the SPI signals will float, causing data corruption or complete transmission failure.
2. **Logic Levels:** Both the STM32H7 and the Raspberry Pi operate at **3.3V logic**. Do not connect the STM32 to the Pi's 5V rail.
