# Sprint 3 - SPI Hardware Validation

## Purpose

Verify that the SPI link between the STM32H743ZI and NVIDIA Jetson Nano is functioning before testing the custom kernel driver.

---

## Objective

Validate

- SPI clock
- Chip Select
- MOSI
- MISO

using the Linux spidev interface.

---

## Hardware

Master

- NVIDIA Jetson Nano

Slave

- STM32H743ZI

---

## Prerequisites

- SPI enabled
- Wiring verified
- STM32 firmware running
- DATA_READY active

---

## Validation

Check available devices

```bash
ls /dev/spidev*
```

Expected

```bash
/dev/spidev0.0
```

(or whichever bus Jetson exposes)

---

## Transfer dummy clocks

```bash
head -c 36 /dev/zero \
| spi-pipe -d /dev/spidev0.0 -s 1000000 \
| hexdump -C
```

Expected Result

```bash
Binary packet received from STM32.
Packet length should match the protocol definition.
```

---

## Pass Criteria

- SPI device detected
- Successful transfer
- Correct packet length
- No timeout
- No CRC / magic failures

---

## Failure Cases

- Wrong SPI mode
- Wrong CS
- Incorrect wiring
- STM32 not responding
- Driver configuration error

---

## Notes

- This validation confirms only the physical SPI bus.
- The custom kernel driver is tested separately.
