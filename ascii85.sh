#!/bin/bash

set -euo pipefail

if [[ "$#" -eq 0 || "$1" == "-e" ]]; then
    g++ -o encoder encode.cpp coder.cpp coder.h
    ./encoder
elif [[ "$1" == "-d" ]]; then
    g++ -o decoder decode.cpp coder.cpp coder.h
    if ! ./decoder; then
        echo "Error: decoding failed" >&2
        exit 1
    fi
else
    echo "Usage: ascii85 [-e | -d]" >&2
    exit 1
fi