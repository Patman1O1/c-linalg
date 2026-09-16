#!/usr/bin/env bash

set -euo pipefail

PROJECT_ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)/.."

conan build "$PROJECT_ROOT"
"$PROJECT_ROOT/build/Release/bin/test_package"
