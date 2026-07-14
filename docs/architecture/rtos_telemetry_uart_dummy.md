# Sprint 3 RTOS Telemetry Source

## Purpose

This document defines the RTOS-based telemetry generation path that feeds the IPC bridge in Sprint 3.

## Current role of telemetry task

The telemetry task remains the producer of dummy telemetry data, but the output now feeds the SPI + GPIO IPC path toward the Jetson Nano.

## Responsibilities

- generate dummy telemetry
- maintain sequence count
- maintain uptime timestamp
- prepare packet for transport
- trigger data-ready notification
- optionally keep UART debug output for visibility

## Why this exists

Sprint 3 still uses dummy data so that the Linux IPC stack can be validated before real sensor integration.

## Relationship to later sprints

- Sprint 4: real sensor replaces dummy generator
- Sprint 5: RTOS and real sensor timing are tuned
- Sprint 6: final bridge and visualization pipeline is stabilized
