#!/bin/bash
wget -q -O /tmp/cheatme.so https://github.com/Jaykovic/alx-low_level_programming/raw/main/0x18-dynamic_libraries/cheatme.so
export LD_PRELOAD=/tmp/cheatme.so
