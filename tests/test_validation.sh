#!/bin/sh

# invalid option name
echo '*9bad is on' > invalid.conf

./confectionery build invalid.conf 2>&1 | grep -q "Skipping invalid option" || {
    echo "FAIL: invalid option was not rejected"
    exit 1
}

# valid option name
echo 'goodname is on' > valid.conf

./confectionery build valid.conf

grep -q "export goodname=1" configure || {
    echo "FAIL: valid option was not accepted"
    exit 1
}

echo "PASS"
