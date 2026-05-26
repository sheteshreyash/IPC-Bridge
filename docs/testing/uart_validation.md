# Sprint 1 UART Validation

## Objective

Verifying STM32 firmware is generating and transmitting dummy telemetry correctly.

## Test setup

- NUCLEO-H753ZI
- USB cable to laptop
- Serial terminal on Ubuntu or Windows

## Test procedure

1. Flash firmware to STM32
2. Open serial terminal at 115200 baud
3. Reset the board
4. Observe repeating telemetry output
5. Verify values change over time
6. Confirm no garbage characters
7. Confirm stable transmission for several minutes

## Expected result

A clean stream of telemetry messages appears in the terminal.

## Pass criteria

- UART works
- board boots correctly
- telemetry is readable
- no crash or freeze
- output frequency is stable enough for Sprint 1

## Failure cases

- wrong baud rate
- wrong UART port
- USB driver issue
- code crash
- bad clock config
