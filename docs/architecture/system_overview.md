# Sprint 1 System Overview

## Goal

Sprint 1 proves the basic embedded telemetry pipeline using the STM32 Nucleo board and the laptop serial terminal.

## Current scope

- STM32 firmware only
- Dummy telemetry generation
- UART transmission over ST-LINK Virtual COM Port
- Serial terminal validation on Windows or Ubuntu

## Current hardware

- STM32 NUCLEO-H743ZI
- USB cable
- Laptop running Windows 11 + Ubuntu 22.04 dual boot
- Serial terminal software such as HTerm, Tera Term, PuTTY, or RealTerm

## High-level architecture

Laptop serial terminal <--- USB VCP ---> STM32 Nucleo board

## Why this sprint exists

This sprint validates:

- board flashing
- UART communication
- telemetry formatting
- repo structure
- documentation workflow

## Not included yet

- FreeRTOS
- DMA
- real sensor
- Raspberry Pi
- Linux kernel driver
- SPI bridge
- visualization pipeline

## Expected outcome

A stable stream of formatted telemetry text on the PC terminal.
