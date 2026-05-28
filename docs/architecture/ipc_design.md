# Sprint 3 IPC Design

## Purpose

This document defines how the STM32 and Raspberry Pi communicate in Sprint 3.

## IPC medium

- Primary transport: SPI
- Synchronization / notification: GPIO DATA_READY line
- Debug fallback: UART on the STM32 side

## Roles

- STM32: real-time producer, SPI slave
- Raspberry Pi: Linux consumer, SPI master
- Kernel driver: bridge between hardware transport and user space
- User-space daemon: logger / analyzer / visualization input

## Why SPI is used

SPI is chosen because:

- it is fast
- it is simple
- it supports deterministic byte transfers
- it is well-supported on Raspberry Pi
- it matches the project goal of low-latency embedded IPC

## Why GPIO is used

SPI slaves cannot initiate transfers by themselves.
The STM32 therefore raises a DATA_READY GPIO line to notify the Pi that a new packet is ready.

## Flow

STM32 packet ready
    -> DATA_READY asserted
Pi interrupt occurs
    -> kernel top half runs
    -> workqueue performs SPI read
    -> packet validated
    -> packet stored in kfifo
    -> user-space reads `/dev/telem0`

## Kernel design

- top half: minimal interrupt handling
- bottom half: SPI read and buffer push
- kfifo: kernel buffering
- character device: user-space access point

## Debug policy

UART remains enabled for debug logs and bring-up verification even though it is not the primary IPC path.

## Future evolution

Later sprints may replace dummy telemetry with real sensor data while keeping the IPC structure unchanged.
