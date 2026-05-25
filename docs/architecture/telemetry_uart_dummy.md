# Sprint 1 Dummy UART Telemetry

## Objective

Generate dummy telemetry data on the STM32 and print it through UART to the laptop serial terminal.

## Telemetry fields

- Sequence number
- Uptime in milliseconds
- AX
- AY
- AZ
- GX
- GY
- GZ

## Format

SEQ=<n>,UPTIME_MS=<n>,AX=<value>mg,AY=<value>mg,AZ=<value>mg,GX=<value>mdps,GY=<value>mdps,GZ=<value>mdps

## Implementation idea

- A telemetry structure stores the values
- A telemetry generator fills the structure
- A formatter converts the structure to text
- UART transmits the formatted string

## Why dummy telemetry is used

Dummy telemetry lets us validate the full STM32-to-terminal pipeline before adding real hardware sensors.
