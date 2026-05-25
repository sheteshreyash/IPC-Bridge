# STM32 IPC Pipeline

A real-time embedded systems project built around:

- STM32H753ZI Nucleo board
- UART telemetry in Sprint 1
- FreeRTOS in Sprint 2
- Linux kernel IPC in later sprints
- Raspberry Pi integration later
- Live visualization and benchmarking later

## Project goal

Build a modular embedded-to-Linux pipeline that starts with dummy telemetry and evolves into a full real-time sensor IPC system.

## Current stage

Sprint 1 — Dummy UART telemetry

## Sprint roadmap

- Sprint 1: Dummy telemetry over UART
- Sprint 2: FreeRTOS scheduling on dummy telemetry
- Sprint 3: Linux IPC bridge for dummy data
- Sprint 4: Real sensor bring-up
- Sprint 5: FreeRTOS on real sensor data
- Sprint 6: Linux IPC + visualization on real sensor data

## Repository structure

- `firmware/` — STM32 code
- `kernel/` — Raspberry Pi Linux driver code
- `user/` — user-space daemon and tools
- `docs/` — architecture, setup, testing, sprint notes
- `tools/` — plotting and utility scripts
- `hardware/` — wiring, BOM, datasheets
- `benchmarks/` — measured outputs and reports
- `scripts/` — build, flash, and run scripts

## Development approach

Build the project in small verified stages.
Do not move to the next sprint until the current one is stable.

## License

MIT License
