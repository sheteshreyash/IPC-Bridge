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

SEQ=&lt;n&gt;,UPTIME_MS=&lt;n&gt;,AX=&lt;value&gt;mg,AY=&lt;value&gt;mg,AZ=&lt;value&gt;mg,GX=&lt;value&gt;mdps,GY=&lt;value&gt;mdps,GZ=&lt;value&gt;mdps

## Implementation idea

- A telemetry structure stores the values
- A telemetry generator fills the structure
- A formatter converts the structure to text
- UART transmits the formatted string

## Why dummy telemetry is used

Dummy telemetry lets us validate the full STM32-to-terminal pipeline before adding real hardware sensors.
