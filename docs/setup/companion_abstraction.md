# Companion Computer Abstraction

## The Core Philosophy

This IPC Bridge is designed to be hardware-agnostic regarding the Linux "Companion Computer." The STM32 Producer and the Linux Userspace Consumer do not care what physical board sits in the middle.

## What Never Changes (The Core IPC)

* **STM32 Firmware:** The FreeRTOS tasks, Packet Builder, and SPI Slave configuration.
* **The Shared ABI:** `telem0_protocol.h` (The packet format).
* **Linux Driver Logic:** The `kfifo`, Workqueue, and Character Device registration in `telem0_driver.c`.
* **Userspace Application:** The C++ `telemetry_reader`.

## What Changes (Board-Specific Implementation)

When porting this project to a new companion computer (e.g., from Jetson Nano to Xavier NX), only the following layer must change:

* **The Device Tree Overlay (`.dts`):** To map the specific SPI controller and IRQ GPIO pins of the new board.
* **Pin Muxing / OS Configuration:** Activating the hardware interfaces via tools like `jetson-io` or `raspi-config`.
* **Physical Wiring:** Adapting jumper wires to the new board's header layout.
