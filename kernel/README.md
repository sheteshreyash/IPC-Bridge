# Sprint 3 Raspberry Pi Kernel Scaffold

This folder contains the first Linux-side scaffold for the IPC bridge.

## Current state

- SPI driver skeleton
- `/dev/telem0` misc device
- placeholder read path
- device-tree overlay placeholder

## Not implemented yet

- IRQ handling
- SPI receive transaction
- kfifo buffering
- DMA
- real Raspberry Pi hardware integration

## Build

```bash
make
```
