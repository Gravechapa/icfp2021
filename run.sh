#!/bin/sh

cd build/src
./icfpc2021 "$@" || echo "run error code: $?"

