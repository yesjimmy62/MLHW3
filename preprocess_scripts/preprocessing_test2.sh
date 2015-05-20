#!/bin/bash -e
cat ./testing_data.txt | sed "s/^.*) //g" \
|tr '[:upper:]' '[:lower:]' > TESTING_WITH_BRACKETS.TXT
