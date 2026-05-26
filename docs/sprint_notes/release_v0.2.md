# Release v0.2 — Sprint 2 Complete

## Release Summary

Sprint 2 introduces FreeRTOS-based scheduling into the IPC-Bridge project.

The project now runs periodic telemetry generation under RTOS task scheduling instead of a polling-based infinite loop.

---

## Features Added

### FreeRTOS Integration

- CMSIS V2 FreeRTOS enabled
- RTOS scheduler initialized successfully
- Multiple concurrent tasks running

### Telemetry Task

- High-priority telemetry task added
- Periodic telemetry generation implemented
- UART transmission moved into RTOS task context

### LED Heartbeat Task

- Low-priority LED task added
- Green, Yellow, and Red LEDs toggled periodically
- Confirms scheduler activity visually

### UART Validation

- Telemetry successfully transmitted over USART3
- HTerm / serial terminal validation completed
- Stable telemetry stream confirmed

### Documentation

- Sprint 2 architecture diagrams added
- RTOS timing and task model documented
- Validation notes completed

---

## Architecture

FreeRTOS Scheduler
    ├── telemetryTask
    ├── ledTask
    └── defaultTask

---

## Hardware Used

- STM32 NUCLEO-H743ZI
- USB connection through ST-LINK VCP
- Windows 11 + Ubuntu 22.04 dual-boot development environment

---

## Validation Completed

- Firmware builds successfully
- FreeRTOS scheduler starts successfully
- Telemetry task runs periodically
- LED task runs concurrently
- UART output stable at 115200 baud
- No scheduler lockups observed

---

## Known Limitations

Current implementation still uses:

- text-based telemetry packets
- blocking UART transmit
- no DMA
- no queues or semaphores
- no external sensor

These will be improved in later sprints.

---

## Future Work

### Sprint 3

- Linux IPC bridge
- Raspberry Pi integration
- userspace receiver
- latency measurements

### Sprint 4

- real sensor integration
- SPI sensor bring-up

### Sprint 5+

- DMA
- binary packets
- CRC validation
- RTOS queue-based telemetry pipeline

---

## Release Tag

Recommended git tag:
v0.2-sprint2
