# Sprint 1 Notes — Dummy Telemetry over UART

## Sprint goal

Get the STM32 Nucleo board to generate dummy telemetry and display it on a laptop serial terminal.

## Scope

Included:

- STM32CubeIDE setup
- USART configuration
- telemetry generator code
- UART output
- serial terminal validation
- documentation and diagrams

Not included:

- FreeRTOS
- DMA
- sensor board
- Raspberry Pi
- Linux kernel driver
- live visualization

## Hardware used

- STM32 NUCLEO-H743ZI
- USB cable
- Laptop with Windows 11 and Ubuntu 22.04
- Serial terminal software

## Validation method

- Flash the board
- Open serial terminal
- Verify formatted telemetry lines
- Confirm sequence count increments
- Confirm output is stable

## Success criteria

- UART output visible
- no build errors
- no runtime crash
- readable telemetry on terminal
- repository documentation updated

## Deliverables

- telemetry.h
- telemetry.c
- updated main.c
- diagrams
- testing notes
- README update
