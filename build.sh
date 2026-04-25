#!/bin/bash
set -e

mkdir -p bin/

gcc -Iinclude $(find src/ -type f -name "*.c") -o ./bin/ctrl

echo "Built!"