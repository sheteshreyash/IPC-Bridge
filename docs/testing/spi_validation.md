# Sprint 3 - SPI Bus Hardware Validation

## Objective

Prove the physical SPI bus is functioning using the standard Linux User-Space driver (`spidev`) before loading our custom kernel module.

## Prerequisites

1. Both boards are powered and wired according to `raspberry_pi_wiring.md`.
2. STM32 is flashed with the Sprint 3 firmware and is actively toggling `DATA_READY`.
3. Raspberry Pi has SPI enabled via `sudo raspi-config`.

## Test Procedure

Because SPI is full-duplex, the Pi (Master) must send dummy clock pulses to force the STM32 (Slave) to shift out data.

Run this command on the Raspberry Pi:

```bash
head -c 36 /dev/zero | spi-pipe -d /dev/spidev0.0 -s 1000000 | hexdump -C
