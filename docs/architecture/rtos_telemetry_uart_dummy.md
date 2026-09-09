# Sprint 4 RTOS Telemetry Source

## Purpose

This document defines the RTOS-based telemetry generation path that feeds the IPC bridge in Sprint 3.
WE have replaced the Sprint 3 dummy telemetry source with real measurements from the MPU-9250 sensor.

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

Sprint 4 introduces real sensor data while maintaining the existing IPC infrastructure.

## Relationship to later sprints

- Sprint 5: real sensor data is fully integrated into the Linux transport path
- Sprint 6: the Linux transport path is redesigned to support multiple telemetry sources alongside the visualization telemetry source
