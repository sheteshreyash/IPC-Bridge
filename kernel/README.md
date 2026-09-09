# Sprint 3 Linux Kernel Driver — Jetson Nano

This directory contains the Linux-side kernel driver for the IPC Bridge project.

## Target Platform

- NVIDIA Jetson Nano Developer Kit P3450 4GB
- Custom Jetson Nano Linux image
- L4T R32.7.1
- Ubuntu 18.04.6 LTS
- Linux 4.9.337-tegra
- AArch64

## STM32 Endpoint

- STM32 NUCLEO-H743ZI
- STM32 acts as SPI slave
- Jetson Nano acts as SPI master
- STM32 produces dummy telemetry at 100 Hz during Sprint 3

## Jetson SPI Interface

Jetson-IO configuration:

- SPI function: `spi1`
- Physical pins: 19, 21, 23, 24, 26

Linux mapping:

- Tegra controller: `7000d400.spi`
- Linux SPI bus: `spi0`
- Chip select: `spi0.0`

Physical SPI connections:

| Jetson Pin | Function | STM32 |
| --- | --- | --- |
| 19 | MOSI | SPI MOSI |
| 21 | MISO | SPI MISO |
| 23 | SCLK | SPI SCLK |
| 24 | CS0 | SPI NSS |
| 31 | DATA_READY | DATA_READY |
| 20 | GND | GND |

## DATA_READY

The Sprint 3 interrupt line uses:

- Jetson physical pin: 31
- Jetson GPIO: 200
- Direction: input
- Trigger: rising edge
- Source: STM32 DATA_READY

GPIO79 / physical pin 12 is not used because the custom Jetson image currently assigns it to `I2S0_SCLK`.

## Driver Architecture

```text
STM32 DATA_READY
       |
       v
Jetson GPIO200
       |
       v
Linux IRQ
       |
       v
telem0_irq_handler()
       |
       v
schedule_work()
       |
       v
telem0_spi_work()
       |
       v
spi_sync()
       |
       v
Packet validation
       |
       v
kfifo
       |
       v
/dev/telem0
       |
       v
User-space telemetry_reader
