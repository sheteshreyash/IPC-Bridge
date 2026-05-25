# Raspberry Pi Setup

## Purpose

The Raspberry Pi will later be used for:

- Linux kernel driver
- SPI communication
- interrupt handling
- user-space data reading
- live visualization

## Current sprint note

Raspberry Pi is not required for Sprint 1.

## Later setup

- Install Raspberry Pi OS Lite 64-bit or Ubuntu Server
- Enable SSH
- Enable SPI
- Install build tools
- Install kernel headers
- Configure driver development environment

## Why Pi is used

The Pi acts as the Linux target in the IPC pipeline.
It allows us to develop and test the Linux kernel driver and user-space components in a real embedded Linux environment, which is crucial for validating our IPC bridge design.
