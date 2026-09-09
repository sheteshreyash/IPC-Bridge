# Sprint 3 - Jetson Nano SPI Loopback Validation

## Objective

Verify the Jetson Nano 40-pin SPI interface independently before connecting the STM32.

This isolates Jetson SPI controller and pinmux functionality from the STM32 firmware.

## Platform

- NVIDIA Jetson Nano Developer Kit P3450 4GB
- L4T R32.7.1
- Linux 4.9.337-tegra
- AArch64

## SPI Configuration

Jetson-IO:

- `spi1`
- Physical pins: 19, 21, 23, 24, 26

Linux:

- Tegra controller: `7000d400.spi`
- Linux SPI bus: `spi0`
- Test device: `/dev/spidev0.0`
- Chip select: CS0

## Wiring

| Jetson Pin | Function |
|---|---|
| 19 | MOSI |
| 21 | MISO |

A jumper was connected between physical pins 19 and 21.

## Test Command

```bash
./spidev_test -D /dev/spidev0.0 -s 1000000 -v -p "12345678"
```
