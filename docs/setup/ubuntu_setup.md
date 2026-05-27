# Ubuntu 22.04 Setup

## Purpose

Ubuntu is the main development environment for:

- STM32 firmware work
- toolchain installation
- Git
- documentation
- later Linux kernel work
- Python plotting

## Install base packages

```bash
sudo apt update && sudo apt upgrade -y

# 1. Core Build Tools & Git
sudo apt install -y build-essential git cmake gdb-multiarch pkg-config

# 2. Kernel Module & Device Tree Tools (Crucial for Sprint 3)
sudo apt install -y linux-headers-$(uname -r) kmod device-tree-compiler

# 3. ARM Toolchains (STM32 Bare-Metal & Raspberry Pi 64-bit OS)
sudo apt install -y gcc-arm-none-eabi binutils-arm-none-eabi gcc-aarch64-linux-gnu

# 4. Hardware Sniffing & Serial Tools
sudo apt install -y picocom socat spi-tools i2c-tools usbutils hexdump

# 5. Python Environment (For later data plotting)
sudo apt install -y python3 python3-pip python3-venv

# 6. DFU Utilities (For flashing STM32 firmware)
sudo apt install dfu-util

# 7. OpenOCD (For debugging STM32 firmware with JTAG/SWD)
sudo apt install openocd

# 8. ST-Link Tools (For flashing and debugging STM32 boards with ST-Link)
sudo apt install stlink-tools
```

## Verify Installations

```bash
    arm-none-eabi-gcc --version        # Proves you can still compile STM32 code
    aarch64-linux-gnu-gcc --version    # Proves you can cross-compile for the Raspberry Pi
    dtc --version                      # Proves the Device Tree Compiler is ready
    picocom --help | head -n 1         # Proves your serial sniffer is installed
    openocd --version                  # Proves OpenOCD is installed
    st-flash --version                 # Proves ST-Link tools are installed
    st-info --probe                    # Proves you can detect your STM32 board with ST-Link
    dfu-util --version                 # Proves DFU utilities are installed
```

## Notes

- Use Ubuntu 22.04 LTS
- Keep all build tools in Ubuntu
- Use Windows only as secondary OS if needed
