#!/usr/bin/env bash

set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
PROJECT_DIR="${ROOT_DIR}/user/telemetry_reader"
BUILD_DIR="${PROJECT_DIR}/build"

rm -rf "${BUILD_DIR}"
mkdir -p "${BUILD_DIR}"

cd "${BUILD_DIR}"

cmake ..
make -j4
