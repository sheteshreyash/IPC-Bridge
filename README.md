# IPC Bridge Project

A modular embedded systems project that evolves from dummy telemetry on an STM32 Nucleo board into a full embedded-to-Linux IPC pipeline.

## Current sprint

Sprint 3 — Linux IPC bridge for dummy telemetry

## Hardware

- STM32 NUCLEO-H743ZI
- Raspberry Pi 4
- Laptop with Windows 11 + Ubuntu 22.04 dual boot

## Current status

- Sprint 1 UART telemetry completed
- Sprint 2 FreeRTOS scheduler integration completed
- Sprint 3 Linux IPC bridge implementation starting

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
- benchmarks/ — measured outputs and reports
- scripts/ — helper scripts

## Development approach

Build one sprint at a time.
Each sprint should be stable and documented before moving on to the next.

## License

MIT
