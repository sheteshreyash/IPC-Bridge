# Sprint 2 FreeRTOS UART Validation

## Objective

Verify that telemetry is generated and transmitted from a FreeRTOS task instead of the bare main loop.

## Test procedure

1. Flash the FreeRTOS-enabled firmware
2. Open HTerm / Tera Term / PuTTY
3. Select the correct COM port
4. Set baud rate to 115200
5. Reset the board
6. Observe periodic telemetry output
7. Confirm values keep changing
8. Confirm scheduler-driven behavior is stable

## Expected result

A clean stream of telemetry lines produced under FreeRTOS task control.

## Pass criteria

- FreeRTOS scheduler starts successfully
- telemetry task runs periodically
- UART output is readable
- no crashes or task lockups
- timing is stable enough for Sprint 2

## Failure cases

- scheduler not starting
- task stack too small
- incorrect FreeRTOS config
- UART not initialized
- output corruption
