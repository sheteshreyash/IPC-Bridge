# Sprint 3 - GPIO Interrupt (IRQ) Validation

This proves that the Pi is actually detecting the 100Hz signal from the STM32.

## Objective

Prove the Raspberry Pi kernel is correctly registering and detecting the 100Hz `DATA_READY` rising edge from the STM32.

## Prerequisites

1. `telem0_overlay.dtbo` is loaded.
2. `telem0_driver.ko` is inserted via `insmod`.

## Test Procedure

The Linux kernel keeps track of all hardware interrupts in a virtual file. We can watch this file update in real-time.

Run this command on the Raspberry Pi:

```bash
watch -n 1 "cat /proc/interrupts | grep telem0"
```
