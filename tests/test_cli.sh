#!/bin/sh

# 1. No arguments
./confectionery 2>&1 | grep -q "Usage" || {
    echo "FAIL: missing arguments did not show usage"
    exit 1
}

# 2. Wrong number of arguments
./confectionery build 2>&1 | grep -q "Usage" || {
    echo "FAIL: wrong argument count did not show usage"
    exit 1
}

# 3. Nonexistent file
./confectionery build does_not_exist.conf 2>&1 | grep -q "could not open" || {
    echo "FAIL: nonexistent file did not produce error"
    exit 1
}

# 4. Missing preset name
echo "[preset speedy]" > PRESETS
./confectionery build PRESETS 2>&1 | grep -q "Usage" || {
    echo "FAIL: missing preset name did not show usage"
    exit 1
}

echo "PASS"
