# Docker Development Environment

## Purpose

The Docker environment provides a reproducible host-side build and validation environment for IPC-Bridge.

It is used for:

- userspace compilation
- Device Tree compilation
- static analysis
- AArch64 cross-compilation tooling
- GitHub Actions CI
- reproducible development environments

## Important Limitation

The Docker environment does not replace the Jetson Nano runtime environment.

The production kernel module must be built against the target Jetson kernel build tree:

```text
Linux 4.9.337-tegra
```
