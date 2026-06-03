#!/usr/bin/env bash

set -e

BUILD_DIR="./_build"
rm -rf "${BUILD_DIR}"
cmake -S . \
      -B "${BUILD_DIR}" \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build "${BUILD_DIR}" -j"$(nproc)"
"./build/bin/LosImages"
echo "ReBuild finished."