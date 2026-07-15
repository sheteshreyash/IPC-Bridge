# Jetson Nano Bring-Up Guide

## 1. OS Installation (JetPack)

* Download the JetPack SD Card Image (JetPack 4.6.x recommended) from Nvidia.
* Flash using Balena Etcher.
* Complete the initial Ubuntu setup via a monitor or headless serial console.

## 2. Environment Preparation

Update the system and install required build tools:

```bash
sudo apt update && sudo apt upgrade -y
sudo apt install build-essential cmake git device-tree-compiler -y
```
