#!/bin/bash

# exit on error
set -ex
cd "$(dirname "$0")/.."

# Make all the test files
make testall

test/bin/node_unit
test/bin/tree_unit

echo "Executing stress tests, this could take a while..."

test/bin/stress_test
