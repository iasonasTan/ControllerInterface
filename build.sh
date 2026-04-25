#!/bin/bash
set -e

mkdir -p bin/

gcc $(find src/ -type f -name "*.c") -o ./bin/ctrl
