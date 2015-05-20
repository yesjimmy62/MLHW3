#!/bin/bash -e
cat ../../../testing_data.txt | sed "s/^.*) //g" \
| tr '[:upper:]' '[:lower:]' \
| sed "s/\[//g"  \
| sed "s/\]//g" > ../preprocessed_files/RAW_TEST_INPUT_WITHOUT_BRACELET.TXT
