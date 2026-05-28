# Sprint 3 — Linux IPC Bridge for Dummy Telemetry

## Goal

Build the first real embedded-to-Linux IPC bridge using dummy telemetry from the STM32 and a Raspberry Pi kernel/user-space path.

## Why this sprint exists

Sprint 3 moves the project from:

- UART-only validation
to
- a real IPC architecture

This is the first sprint where the STM32 and Raspberry Pi communicate as two separate systems.

## Current scope

Included:

- STM32 FreeRTOS telemetry generation
- dummy telemetry packet creation
- DATA_READY GPIO notification
- Raspberry Pi SPI receive path
- Linux kernel driver
- kfifo buffering
- character device exposure
- user-space reading and logging
- architecture and timing documentation

Not included yet:

- real sensor board
- final sensor calibration
- DMA optimization for real sensor data
- advanced loss recovery
- final live plotting polish

## High-level architecture

STM32 FreeRTOS telemetry task
-> packet builder
-> DATA_READY GPIO
-> Raspberry Pi kernel driver
-> kfifo
-> /dev/telem0
-> user-space daemon
-> CSV / plots

## What Sprint 3 validates

- SPI transfer path between STM32 and Pi
- interrupt-driven notification using GPIO
- Linux kernel module skeleton
- kernel to user-space bridge
- packet flow consistency
- first latency observations

## Expected outcome

A dummy-data IPC bridge that is visible from user space on the Raspberry Pi and can be logged or plotted.

## Deliverables

- updated architecture docs
- updated data flow docs
- updated timing docs
- IPC design docs
- packet format docs
- Sprint 3 release note
- screenshots of validation
- kernel and user-space code later in the sprint
