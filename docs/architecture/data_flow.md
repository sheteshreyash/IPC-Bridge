# Sprint 1 Data Flow

## Data flow summary

The STM32 generates dummy telemetry values in firmware, formats them as text, and sends them to the laptop over UART via the board's Virtual COM Port.

## Flow steps

1. STM32 boots
2. Clock and UART are initialized
3. Main loop generates dummy telemetry values
4. Data is formatted into a readable string
5. UART transmits the string
6. USB ST-LINK converts the UART stream into a Virtual COM Port on the laptop
7. Serial terminal displays the output

## Data format example

SEQ=12,UPTIME_MS=12,AX=-345mg,AY=111mg,AZ=1023mg,GX=...

## Data characteristics

- text-based
- human readable
- low complexity
- easy to validate in Sprint 1

## Reason for text format

Text format is ideal for first bring-up because it is easy to debug in a serial terminal without needing any parser.
