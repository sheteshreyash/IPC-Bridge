# NVIDIA Jetson Nano Setup

## Purpose

This document describes the complete bring-up procedure for the NVIDIA Jetson Nano Developer Kit used as the Linux-side IPC consumer during Sprint 3.

The Jetson Nano is responsible for:

- Receiving interrupt notifications from the STM32
- Acting as the SPI Master
- Running the Linux kernel driver
- Exposing telemetry through `/dev/telem0`
- Running user-space applications for validation and future visualization

This document intentionally covers only software installation and platform preparation.

---

## Hardware

Board

- NVIDIA Jetson Nano Developer Kit
- P3450 4GB

Operating System

- Ubuntu (JetPack supplied)

Communication

- SPI Master
- GPIO Interrupt
- UART (optional)

---

## Project Role

The overall project architecture is

MPU-9250
↓

STM32H743ZI
↓

SPI Slave

↓

Jetson Nano SPI Master

↓

Linux Kernel Driver

↓

kfifo

↓

/dev/telem0

↓

telemetry_reader

↓

Visualization (Sprint 6)

---

## Recommended JetPack Version

Use the latest stable JetPack officially supporting the Jetson Nano.

Recommended:

JetPack 4.6.x

Reasons

- Stable Linux kernel
- Mature SPI support
- Excellent documentation
- Compatible with Linux kernel module development

Avoid experimental releases until the IPC bridge is complete.

---

## Flash JetPack

Download

NVIDIA SDK Manager

or

Official JetPack SD Card Image

Flash the microSD card using

Balena Etcher

After flashing

Insert SD card

Power Jetson

Complete Ubuntu setup

---

## First Boot

Configure

Username

Password

Hostname

Time Zone

Keyboard Layout

Network

Reboot after first login.

---

## Update Ubuntu

```bash
sudo apt update
sudo apt upgrade -y
```

---

## Install Development Packages

```bash
sudo apt install -y \
build-essential \
git \
cmake \
pkg-config \
device-tree-compiler \
kmod \
clang \
clang-format \
cppcheck \
python3 \
python3-pip \
python3-venv
```

---

## Install Kernel Headers

Check kernel version

```bash
uname -r
```

Install matching headers

```bash
sudo apt install linux-headers-$(uname -r)
```

Verify

```bash
ls /lib/modules/$(uname -r)/build
```

---

## Verify SPI Devices

```bash
ls /dev/spidev*
```

Expected

```bash
/dev/spidev0.0
/dev/spidev0.1
```

Device names may differ depending on JetPack version.

---

## Verify GPIO

List GPIO controllers

```bash
gpiodetect
```

List GPIO lines

```bash
gpioinfo
```

These commands confirm the GPIO subsystem is functioning.

---

## Verify Kernel Module Environment

Compile a sample module

```bash
cd kernel

make
```

Expected output

```bash
telem0_driver.ko
```

---

## Verify Device Tree Compiler

```bash
dtc --version
```

Expected

```bash
Version 1.x.x
```

---

## Build User-space Reader

```bash
cd user/telemetry_reader

cmake -S . -B build

cmake --build build
```

Expected

```bash
telemetry_reader
```

---

## Build Scripts

The repository provides helper scripts.

Build Kernel Driver

```bash
./scripts/build_pi_driver.sh
```

(Build script name will be renamed in future to reflect Jetson.)

Build User Reader

```bash
./scripts/build_user_reader.sh
```

---

## SPI Validation (Future)

After hardware wiring

Verify

- SPI Clock
- MOSI
- MISO
- Chip Select

using

- oscilloscope
- logic analyzer

---

## GPIO Interrupt Validation

Verify

DATA_READY

using

```bash
gpiomon
```

Expected

GPIO interrupt events.

---

## Kernel Driver Validation

Compile

```bash
make
```

Load

```bash
sudo insmod telem0_driver.ko
```

Verify

```bash
lsmod | grep telem0
```

Check logs

```bash
sudo dmesg
```

Unload

```bash
sudo rmmod telem0_driver
```

---

## Character Device Validation

After driver loads

```bash
ls /dev/telem0
```

Expected

```bash
/dev/telem0
```

---

## User-space Validation

Run

```bash
./telemetry_reader
```

Expected

Dummy telemetry packets

or

Polling waits until packets arrive.

---

## Common Commands

Kernel Version

```bash
uname -r
```

Loaded Modules

```bash
lsmod
```

Module Information

```bash
modinfo telem0_driver.ko
```

Kernel Log

```bash
sudo dmesg
```

Remove Module

```bash
sudo rmmod telem0_driver
```

Insert Module

```bash
sudo insmod telem0_driver.ko
```

SPI Devices

```bash
ls /dev/spidev*
```

GPIO

```bash
gpioinfo
```

---

## Common Problems

## Secure Boot

Unsigned kernel modules may be rejected.

Disable Secure Boot if required.

---

## Missing Kernel Headers

Install

```bash
linux-headers-$(uname -r)
```

---

## SPI Device Missing

Verify

- SPI enabled
- Device Tree
- Kernel configuration

---

## GPIO Interrupt Missing

Verify

- Wiring
- GPIO number
- Interrupt polarity

---

## Driver Builds but Does Not Load

Check

```bash
sudo dmesg
```

for

- symbol mismatch
- version mismatch
- secure boot

---

## Future Work

Sprint 4

- Hardware validation
- SPI communication
- IRQ handling
- Kernel buffering

Sprint 5

- Replace dummy telemetry
- MPU-9250 integration

Sprint 6

- Real-time visualization
- Latency benchmarking
- Throughput optimization
- Performance profiling

---

## Document Revision

Version

Sprint 3

Author

Shreyash Shete

Status

Ready for Jetson Nano bring-up
