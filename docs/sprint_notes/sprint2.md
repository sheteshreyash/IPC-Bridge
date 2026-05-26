# Sprint 2 — FreeRTOS on Dummy Telemetry

## Goal

Convert the Sprint 1 polling-style telemetry generator into a FreeRTOS-based design that schedules telemetry generation and UART transmission through tasks.

## Scope

Included:

- FreeRTOS integration
- task creation
- telemetry generation under scheduler control
- UART validation from task context
- documentation and diagrams for RTOS architecture

Not included:

- DMA
- external sensor
- Raspberry Pi
- Linux kernel driver
- IPC bridge
- visualization pipeline

## Why this sprint exists

This sprint proves that:

- the project can run under an RTOS
- telemetry can be scheduled cleanly
- timing is more structured than plain main-loop polling
- the codebase is ready for later driver and IPC stages

## Suggested task model

- Telemetry Task
- Optional Monitor / Health Task
- Idle task
- Optional future logging task

## Expected output

A stable telemetry stream produced by FreeRTOS tasks and printed on the serial terminal.

## Validation method

- Flash firmware
- Open serial terminal
- Confirm output appears periodically
- Confirm task-based scheduling is working
- Confirm telemetry values still update correctly

## Deliverables

- FreeRTOS-enabled STM32 project
- updated telemetry source
- updated main application
- diagrams
- testing notes
- sprint documentation
