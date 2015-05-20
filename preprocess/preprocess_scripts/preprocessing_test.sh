#!/bin/bash -e
cat ./testing_data.txt | sed "s/^.*) //g" \
| tr '[:upper:]' '[:lower:]' \
| sed "s/\[//g"  \
| sed "s/\]//g" > TESTING.TXT
