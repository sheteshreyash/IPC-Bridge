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

sudo apt install -y \
build-essential git cmake make gcc g++ gdb gdb-multiarch \
curl wget unzip pkg-config \
bc bison flex libssl-dev libelf-dev libncurses-dev \
device-tree-compiler kmod \
python3 python3-pip python3-venv \
minicom picocom screen usbutils
```

## ARM toolchains

```bash
sudo apt install -y gcc-arm-none-eabi binutils-arm-none-eabi
sudo apt install -y gcc-arm-linux-gnueabihf
```

verify with :

```bash
arm-none-eabi-gcc --version
arm-linux-gnueabihf-gcc --version
git --version
python3 --version
```

## Notes

- Use Ubuntu 22.04 LTS
- Keep all build tools in Ubuntu
- Use Windows only as secondary OS if needed
