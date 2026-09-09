# Sprint 3 - SPI Hardware Validation

## Purpose

Verify the STM32H743ZI-to-Jetson Nano SPI communication path used by the IPC bridge.

## Objective

Validate:

- SPI clock
- chip select
- MOSI
- MISO
- packet transfer

## Hardware

### Master

- NVIDIA Jetson Nano

### Slave

- STM32H743ZI

## Connections

| Jetson Pin | Function | STM32 |
|---|---|---|
| 19 | MOSI | PA7 / SPI1_MOSI |
| 21 | MISO | PA6 / SPI1_MISO |
| 23 | SCLK | PA5 / SPI1_SCK |
| 24 | CS0 | PA4 / SPI1_NSS |
| 31 | DATA_READY | PB1 |
| 20 | GND | GND |

## Validation Strategy

### Stage 1

Validate the Jetson SPI controller using the physical loopback test documented in:

```text# Sprint 3 - SPI Hardware Validation

## Purpose

Verify the Jetson SPI interface and the STM32-to-Jetson SPI transport used by the IPC bridge.

---

## Objective

Validate:

- SPI clock
- Chip Select
- MOSI
- MISO
- packet transfer

using an incremental test strategy.

---

## Stage 1 - Jetson SPI Loopback

Before connecting the STM32, validate the Jetson SPI hardware using `/dev/spidev0.0`.

See:

```text
docs/testing/jetson_spi_loopback.md
```

docs/testing/jetson_spi_loopback.md
```
