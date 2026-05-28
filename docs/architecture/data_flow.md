# Sprint 3 Data Flow

## Data flow summary

In Sprint 3, the STM32 generates dummy telemetry under FreeRTOS, places it into a packet, asserts a DATA_READY GPIO line, and the Raspberry Pi fetches the packet over SPI as the master.

## Flow steps

1. STM32 boots and initializes clocks, GPIO, UART, SPI, and FreeRTOS
2. Telemetry task generates dummy telemetry values
3. Telemetry task formats values into a fixed packet
4. STM32 stores packet in a transmit buffer
5. STM32 asserts DATA_READY GPIO
6. Raspberry Pi GPIO interrupt fires
7. Linux kernel driver schedules bottom-half work
8. Driver reads packet over SPI
9. Driver validates packet and pushes it into kfifo
10. User-space daemon reads from `/dev/telem0`
11. Daemon logs and optionally visualizes the data

## Data format example

SEQ=12,TS_US=123456,AX=-345,AY=111,AZ=1023,GX=10,GY=11,GZ=-3

## Data characteristics

- fixed-format
- machine-readable
- low latency
- suitable for kernel/user-space handoff
- still based on dummy data for now

## Why this flow matters

This sprint removes UART-only assumptions and proves the embedded-to-Linux bridge path using a real IPC architecture.
It sets the stage for later sprints to replace dummy telemetry with real sensor data while keeping the same flow.
