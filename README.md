# IPC Bridge Project

A modular embedded systems project that starts with dummy telemetry on an STM32 Nucleo board and evolves into a full embedded-to-Linux IPC pipeline.

## Current sprint

Sprint 1 — Dummy telemetry over UART

## Hardware

- STM32 NUCLEO-H743ZI
- Laptop with Windows 11 + Ubuntu 22.04 dual boot

## Current status

- Sprint 1 UART telemetry completed
- Sprint 2 FreeRTOS scheduler integration in progress

## Sprint roadmap

- Sprint 1: Dummy telemetry over UART
- Sprint 2: FreeRTOS on dummy telemetry
- Sprint 3: Linux IPC bridge for dummy telemetry
- Sprint 4: Real sensor bring-up
- Sprint 5: FreeRTOS on real sensor data
- Sprint 6: Linux IPC bridge and visualization on real sensor data

## Repository structure

- docs/ — architecture, setup, testing, sprint notes
- firmware/ — STM32 code
- kernel/ — Raspberry Pi kernel work
- user/ — user-space tools and daemons
- tools/ — helper scripts
- hardware/ — wiring and BOM notes
- benchmarks/ — measured outputs
- scripts/ — helper scripts

## Development approach

Build one sprint at a time.
Each sprint adds a small piece of functionality and validates it before moving on.

## License

MIT
