# Sprint 1 — Dummy UART Telemetry from STM32

## Goal

Create a simple STM32 firmware that generates dummy telemetry data and sends it to a laptop serial terminal over UART.

## Scope

Included:

- STM32CubeIDE project setup
- UART initialization
- Dummy telemetry generation
- UART transmission
- Serial terminal validation
- Documentation and diagrams

Not included:

- FreeRTOS
- DMA
- External sensor integration
- Raspberry Pi
- Linux kernel driver
- Visualization pipeline

## Why this sprint exists

This sprint proves that:

- the board is working
- flashing is working
- UART output is working
- the repository structure is correct
- documentation workflow is in place

## Expected Output

A repeating telemetry line such as:

AX:123 AY:456 AZ:789 CNT:42

or a more structured format such as:

SEQ=42,TIME=123456,AX=123,AY=456,AZ=789

## STM32 Configuration

- Board: NUCLEO-H753ZI
- Tool: STM32CubeIDE
- UART: USART3 / VCP
- Baud rate: 115200
- Parity: None
- Stop bits: 1
- Word length: 8 bits

## Validation Method

- Flash firmware
- Open serial terminal on Ubuntu or Windows
- Observe repeating dummy telemetry
- Confirm stable transmission

## Deliverables

- Working CubeIDE project
- Source code
- Screenshot of serial output
- Block diagram
- Sequence diagram
- Timing diagram
- Updated README
