#!/bin/bash

# exit on error
set -ex
cd "$(dirname "$0")/.."

# Make all the test files
make memtest

valgrind test/bin/memtest

make clean
