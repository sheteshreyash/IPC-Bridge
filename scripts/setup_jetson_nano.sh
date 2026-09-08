#!/usr/bin/env bash
#
# IPC-Bridge - Jetson Nano P3450 4GB setup
#
# This script is intended for the custom Jetson Nano image described by:
# https://github.com/helmutbuhler/jetson_nano_image_milana
#
# It automates the post-first-boot setup steps that are safe to automate.
# SD-card flashing and the interactive Jetson-IO pin configuration remain
# manual because they require physical/interactive choices.
#
# Target platform used by this project:
#   Jetson Nano P3450 4GB
#   Ubuntu 18.04.x
#   L4T R32.7.x
#   Linux 4.9.x-tegra
#   aarch64
#
# Run AFTER:
#   1. Flashing the custom ISO to the microSD card.
#   2. Completing first-boot username/password configuration.
#   3. Establishing network access.
#
# Usage:
#   chmod +x scripts/setup_jetson_nano.sh
#   sudo ./scripts/setup_jetson_nano.sh
#

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"
LOG_FILE="${ROOT_DIR}/jetson_setup.log"
TARGET_USER="${SUDO_USER:-$(id -un)}"

section() {
    echo
    echo "============================================================"
    echo "$*"
    echo "============================================================"
}

warn() {
    echo "WARNING: $*" >&2
}

fail() {
    echo "ERROR: $*" >&2
    exit 1
}

[[ "${EUID}" -eq 0 ]] || fail "Run this script with sudo."

exec > >(tee -a "${LOG_FILE}") 2>&1

section "0. Verify Jetson platform"

MODEL="$(tr '\0' '\n' < /proc/device-tree/model 2>/dev/null || true)"
L4T_RELEASE="$(cat /etc/nv_tegra_release 2>/dev/null || true)"
KERNEL="$(uname -r)"
ARCH="$(uname -m)"

printf 'Model        : %s\n' "${MODEL}"
printf 'Kernel       : %s\n' "${KERNEL}"
printf 'Architecture : %s\n' "${ARCH}"
printf 'L4T release  : %s\n' "${L4T_RELEASE}"
printf 'Target user  : %s\n' "${TARGET_USER}"
printf 'Repo root    : %s\n' "${ROOT_DIR}"

[[ "${ARCH}" == "aarch64" ]] || warn "Architecture is not aarch64. This script targets Jetson Nano aarch64."
[[ "${KERNEL}" == *"tegra"* ]] || warn "Running kernel does not contain 'tegra'. Verify the Jetson image before continuing."

if [[ -f /etc/os-release ]]; then
    . /etc/os-release
    echo "OS           : ${PRETTY_NAME:-unknown}"
fi

section "1. Update package lists"
apt-get update

section "2. Install IPC-Bridge development packages"
apt-get install -y \
    build-essential \
    git \
    cmake \
    pkg-config \
    device-tree-compiler \
    kmod \
    openssh-server \
    gpiod \
    i2c-tools \
    usbutils \
    python3 \
    python3-pip \
    python3-venv \
    clang \
    clang-format \
    cppcheck \
    screen

section "3. Verify matching NVIDIA kernel headers"
KERNEL_BUILD="/lib/modules/${KERNEL}/build"

if [[ -e "${KERNEL_BUILD}/Makefile" ]]; then
    echo "Kernel build tree:"
    readlink -f "${KERNEL_BUILD}"
    echo "Kernel build version:"
    make -C "${KERNEL_BUILD}" kernelversion
else
    echo "Matching kernel build tree is missing."
    if apt-cache show nvidia-l4t-kernel-headers >/dev/null 2>&1; then
        apt-get install -y nvidia-l4t-kernel-headers
    else
        fail "nvidia-l4t-kernel-headers is unavailable and ${KERNEL_BUILD} is missing."
    fi
    [[ -e "${KERNEL_BUILD}/Makefile" ]] || fail "Kernel build tree is still missing: ${KERNEL_BUILD}"
fi

section "4. Hold custom-kernel packages BEFORE any upgrade"

# These are the exact NVIDIA packages named by the custom-image README.
NVIDIA_HOLD_PACKAGES=(
    nvidia-l4t-kernel
    nvidia-l4t-kernel-dtbs
    nvidia-l4t-kernel-headers
    nvidia-l4t-bootloader
    nvidia-l4t-jetson-io
)

INSTALLED_HOLD_PACKAGES=()
for pkg in "${NVIDIA_HOLD_PACKAGES[@]}"; do
    if dpkg-query -W -f='${Status}\n' "${pkg}" 2>/dev/null | grep -q 'install ok installed'; then
        INSTALLED_HOLD_PACKAGES+=("${pkg}")
    fi
done

if (( ${#INSTALLED_HOLD_PACKAGES[@]} )); then
    apt-mark hold "${INSTALLED_HOLD_PACKAGES[@]}"
fi

echo "Current holds:"
apt-mark showhold || true

section "5. Optional desktop-package cleanup"
cat <<'CLEANUP_NOTICE'
The custom-image README provides an optional command to remove large
GUI/desktop applications when they are not needed. This is NOT required
for IPC-Bridge operation.

The script will ask before running it.
CLEANUP_NOTICE

read -r -p "Run optional desktop-package cleanup from the custom-image README? [y/N] " DO_CLEANUP

if [[ "${DO_CLEANUP}" =~ ^[Yy]$ ]]; then
    apt-get remove -y \
        libreoffice-writer \
        libreoffice-avmedia-backend-gstreamer \
        libreoffice-base-core \
        libreoffice-calc \
        libreoffice-common \
        libreoffice-core \
        libreoffice-draw \
        libreoffice-gnome \
        libreoffice-gtk3 \
        libreoffice-impress \
        libreoffice-math \
        libreoffice-ogltrans \
        libreoffice-pdfimport \
        libreoffice-style-breeze \
        libreoffice-style-galaxy \
        libreoffice-style-tango \
        chromium-browser \
        'chromium*' \
        yelp \
        unity \
        thunderbird \
        rhythmbox \
        nautilus \
        gnome-software || true
    apt-get autoremove -y
else
    echo "Skipping optional desktop cleanup."
fi

section "6. Upgrade packages with custom kernel packages held"
apt-get upgrade -y

section "7. Initialize optional extra UART"

if systemctl list-unit-files 2>/dev/null | grep -q '^nvgetty\.service'; then
    systemctl stop nvgetty || true
    systemctl disable nvgetty || true
else
    echo "nvgetty.service not installed; continuing."
fi

udevadm trigger

if getent group dialout >/dev/null 2>&1; then
    usermod -aG dialout "${TARGET_USER}" || true
fi

# Apply the custom-image README's permissions when those device nodes exist.
for dev in /dev/ttyS0 /dev/ttyTHS1; do
    if [[ -e "${dev}" ]]; then
        chmod 666 "${dev}" || true
        echo "UART available: ${dev}"
    fi
done

section "8. Enable SSH for headless development"
systemctl enable ssh
systemctl restart ssh
systemctl --no-pager --full status ssh || true

section "9. GPIO group access"
if ! getent group gpio >/dev/null 2>&1; then
    groupadd gpio
fi
usermod -aG gpio "${TARGET_USER}" || true

echo "User groups after setup:" 
# getent reflects the account database; a new login is required to activate it in the shell.
id "${TARGET_USER}" || true

section "10. Verify custom-image SPI behavior"

# The custom-image README states that spidev is loaded automatically at boot.
# Therefore this script does not make modprobe a permanent requirement.
if lsmod | grep -q '^spidev'; then
    echo "spidev is already loaded."
else
    echo "spidev is not currently loaded; loading it once now for verification."
    modprobe spidev || warn "Could not load spidev. Investigate before SPI bring-up."
fi

# Verify the SPI character devices if present.
echo "SPI device nodes:"
ls -la /dev/spidev* 2>/dev/null || echo "No /dev/spidev* nodes detected yet."

echo "SPI sysfs devices:"
ls -la /sys/bus/spi/devices/ 2>/dev/null || true

section "11. Jetson-IO SPI configuration (MANUAL)"
JETSON_IO="/opt/nvidia/jetson-io/jetson-io.py"
[[ -x "${JETSON_IO}" ]] || fail "Jetson-IO not found at ${JETSON_IO}"

cat <<'JETSONIO'
The custom-image README requires an interactive Jetson-IO configuration:

  1. Configure 40 pin
  2. Configure header pins manually
  3. Enable spi1 and/or spi2 as required
  4. Save pin changes
  5. Save without reboot

For this IPC-Bridge project, do not enable unrelated functions.
The current Sprint 3 design targets the SPI interface on the Jetson Nano
40-pin header and uses a separate GPIO line for DATA_READY.

The script will open Jetson-IO now. Complete the configuration manually,
then return to this terminal.
JETSONIO

read -r -p "Press ENTER to open Jetson-IO, or Ctrl+C to stop: " _
"${JETSON_IO}"

section "12. Verify SPI after Jetson-IO"
udevadm trigger || true
udevadm settle || true

# On the custom image spidev is expected to load automatically, but keep a
# fallback modprobe in case this current boot did not load it.
if ! lsmod | grep -q '^spidev'; then
    modprobe spidev || warn "spidev could not be loaded after Jetson-IO."
fi

ls -la /dev/spidev* 2>/dev/null || echo "No /dev/spidev* nodes found."
ls -la /sys/class/spidev/ 2>/dev/null || true

section "13. Verify GPIO subsystem"
ls -la /dev/gpiochip* 2>/dev/null || echo "No /dev/gpiochip* nodes found."
if command -v gpiodetect >/dev/null 2>&1; then
    gpiodetect || true
fi

section "14. Verify development tools"
echo "gcc:   $(gcc --version | head -n 1)"
echo "g++:   $(g++ --version | head -n 1)"
echo "make:  $(make --version | head -n 1)"
echo "cmake: $(cmake --version | head -n 1)"
echo "dtc:   $(dtc --version 2>&1 | head -n 1)"
echo "kmod:  $(kmod --version | head -n 1)"
echo "python: $(python3 --version)"
echo "git:   $(git --version)"

section "15. Verify IPC-Bridge repository"
[[ -d "${ROOT_DIR}/kernel" ]] && echo "kernel/                         OK" || warn "kernel/ missing"
[[ -f "${ROOT_DIR}/kernel/Makefile" ]] && echo "kernel/Makefile                 OK" || warn "kernel/Makefile missing"
[[ -f "${ROOT_DIR}/kernel/telem0_driver.c" ]] && echo "kernel/telem0_driver.c          OK" || warn "telem0_driver.c missing"
[[ -f "${ROOT_DIR}/kernel/dts/telem0_overlay.dts" ]] && echo "kernel/dts/telem0_overlay.dts   OK" || warn "telemetry overlay missing"
[[ -f "${ROOT_DIR}/shared/telem0_protocol.h" ]] && echo "shared/telem0_protocol.h         OK" || warn "shared protocol missing"
[[ -f "${ROOT_DIR}/user/telemetry_reader/CMakeLists.txt" ]] && echo "userspace CMake project           OK" || warn "userspace project missing"

section "16. Optional IPC-Bridge native builds"
read -r -p "Build the kernel driver and telemetry reader now? [y/N] " BUILD_NOW

if [[ "${BUILD_NOW}" =~ ^[Yy]$ ]]; then
    echo "Building kernel driver against: $(uname -r)"
    cd "${ROOT_DIR}/kernel"
    make clean
    make
    [[ -f telem0_driver.ko ]] || fail "Kernel module build completed without telem0_driver.ko"
    file telem0_driver.ko
    modinfo telem0_driver.ko || true

    echo "Building userspace reader..."
    cd "${ROOT_DIR}/user/telemetry_reader"
    rm -rf build
    cmake -S . -B build
    cmake --build build -j"$(nproc)"
    [[ -x build/telemetry_reader ]] || fail "telemetry_reader build did not produce an executable"
    file build/telemetry_reader
else
    echo "Skipping IPC-Bridge builds."
fi

section "17. Final status"
echo "Model        : ${MODEL}"
echo "Kernel       : $(uname -r)"
echo "Architecture : $(uname -m)"
echo "L4T          : $(cat /etc/nv_tegra_release 2>/dev/null || true)"
echo
printf 'Held NVIDIA packages:\n'
apt-mark showhold || true

echo
echo "SPI device nodes:"
ls -la /dev/spidev* 2>/dev/null || echo "None"

echo
echo "Kernel build tree:"
readlink -f "/lib/modules/$(uname -r)/build" 2>/dev/null || true

echo
echo "SSH:"
echo "enabled: $(systemctl is-enabled ssh 2>/dev/null || true)"
echo "active : $(systemctl is-active ssh 2>/dev/null || true)"

echo
section "DONE"

echo "Setup log: ${LOG_FILE}"
echo "Start a NEW SSH/login session before relying on gpio/dialout group membership."
echo "Next Sprint 3 validation: SPI loopback -> Jetson GPIO/DATA_READY -> telem0_driver -> kfifo -> /dev/telem0."
