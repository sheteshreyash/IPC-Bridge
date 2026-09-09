# Sprint 1 UART Validation

## Objective

Verify that the STM32 firmware generates and transmits dummy telemetry correctly.

## Test Setup

- NUCLEO-H743ZI
- USB cable to laptop
- Serial terminal on Ubuntu or Windows

## Test Procedure

1. Flash firmware to STM32
2. Open serial terminal at 115200 baud
3. Reset the board
4. Observe repeating telemetry output
5. Verify values change over time
6. Confirm no garbage characters
7. Confirm stable transmission for several minutes

## Expected Result

A clean stream of telemetry messages appears in the terminal.

## Pass Criteria

- UART works
- board boots correctly
- telemetry is readable
- no crash or freeze
- output frequency is stable enough for Sprint 1

## Failure Cases

- wrong baud rate
- wrong UART port
- USB driver issue
- firmware crash
- incorrect clock configuration
- output corruption

## Later Sprint Usage

UART remains a diagnostic interface.

During Sprint 4 it is used to inspect MPU-9250 sensor values before those values are sent through the Jetson IPC pipeline.
