#!/usr/bin/env bash

set -euo pipefail

BUILD_TYPE="${1:-Release}"

PROJECT_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)/.."

conan build "$PROJECT_ROOT" -o "&:build_tests=True" -s "build_type=$BUILD_TYPE"
"$PROJECT_ROOT/build/$BUILD_TYPE/bin/c_linalg_test"
