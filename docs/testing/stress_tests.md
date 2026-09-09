# Sprint 3 - Stress Testing

## Purpose

Evaluate long-duration stability of the IPC bridge.

---

## Objectives

Verify

- continuous operation
- memory stability
- interrupt stability
- packet integrity

---

## Test 1

- Continuous Run
- Duration : 1 hour
- Expected: No crashes

---

## Test 2

- High Frequency
- Increase telemetry frequency.

### Verify this

- packet loss
- CPU usage
- interrupt handling

---

## Test 3

### Kernel Reload

Repeatedly

```bash
sudo insmod telem0_driver.ko
sudo rmmod telem0_driver
```

### Verify that

```dmesg
no kernel panic
no memory leak
```

---

## Test 4

- Reader Restart
- Repeatedly restart
- telemetry_reader

### Verify

```dmesg
reconnect succeeds
no stale descriptors
```

---

## Test 5

STM32 Reset

Reset STM32 while Jetson remains running.

### Verify test 5

driver recovery
SPI recovery
IRQ recovery
Pass Criteria
Stable operation
No kernel warnings
No oops
No panic
No packet corruption
Future

---

## Sprint 6 introduces

- DMA stress testing
- visualization stress testing
- high-rate IMU streaming
