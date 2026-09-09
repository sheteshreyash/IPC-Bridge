# Sprint 4 — MPU-9250 WHO_AM_I Validation

## Objective

Verify that the STM32 can communicate with the MPU-9250 and identify the device before attempting continuous sensor acquisition.

## Procedure

1. Connect the MPU-9250 to the STM32 sensor interface.
2. Power the sensor using the correct voltage.
3. Initialize the selected sensor bus.
4. Read the MPU-9250 WHO_AM_I register.
5. Print the returned value over UART.
6. Repeat the test after reset.

## Pass Criteria

- sensor communication succeeds
- expected WHO_AM_I value is returned
- no repeated bus errors
- value remains stable across resets

## Failure Cases

- no response
- incorrect address
- incorrect bus configuration
- unstable communication
- incorrect power or wiring
