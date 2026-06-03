#!/usr/bin/env bash

set -e

BUILD_DIR="./_build"
cmake -S . \
      -B "${BUILD_DIR}" \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "${BUILD_DIR}" -j"$(nproc)"
"./build/bin/LosImages"
echo "Build finished."