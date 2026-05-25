# STM32CubeIDE Setup

## Purpose

STM32CubeIDE is used to:

- create the STM32 project
- configure peripherals
- generate code
- flash the Nucleo board
- debug firmware

## Minimum setup

- Install STM32CubeIDE
- Install STM32CubeProgrammer
- Install ST-LINK drivers if needed
- Ensure the Nucleo board is detected

## Sprint 1 peripheral setup

- Board: NUCLEO-H753ZI
- UART: USART3 / VCP
- Baud rate: 115200
- No DMA yet
- No FreeRTOS yet

## Verification

- Create a test project
- Build successfully
- Flash successfully
- See serial data in terminal
