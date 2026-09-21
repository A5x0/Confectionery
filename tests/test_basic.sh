#!/bin/sh

echo 'foo is on' > basic.conf
echo 'bar is off' >> basic.conf

./confectionery build basic.conf

grep -q "export foo=1" configure || {
    echo "FAIL: foo was not enabled"
    exit 1
}

grep -q "export bar=0" configure || {
    echo "FAIL: bar was not disabled"
    exit 1
}

echo "PASS"
