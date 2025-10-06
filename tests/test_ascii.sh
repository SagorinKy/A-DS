#!/bin/bash
set -e

if [[ ! -f "../encode.cpp" || ! -f "../decode.cpp" || ! -f "../coder.cpp" || ! -f "../coder.h" ]]; then
    echo "Error: files encode.cpp, decode.cpp, coder.cpp или coder.h aren't found"
    exit 1
fi

g++ -o encoder ../encode.cpp ../coder.cpp ../coder.h
g++ -o decoder ../decode.cpp ../coder.cpp ../coder.h
python3 test.py

echo "ALL TESTS DONE"