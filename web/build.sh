#!/bin/sh

emcmake cmake -B build || exit 1
cmake --build build || exit 1
cp static/* build/

