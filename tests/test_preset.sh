#!/bin/sh

cat > PRESETS <<EOF
[preset speedy]
fast is on
slow is off

[preset safe]
fast is off
slow is on
EOF

./confectionery build PRESETS speedy

grep -q "export fast=1" configure || {
    echo "FAIL: fast was not enabled in speedy preset"
    exit 1
}

grep -q "export slow=0" configure || {
    echo "FAIL: slow was not disabled in speedy preset"
    exit 1
}

echo "PASS"
