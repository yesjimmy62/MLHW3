#!/bin/bash -e
cat ../../../testing_data.txt | sed "s/^.*) //g" \
| sed "s/[,!\.]/ /g" \
| sed "s/[ \t]+/ /g" \
|tr '[:upper:]' '[:lower:]' >  ../preprocessed_files/RAW_TEST_INPUT_WITH_BRACKET.TXT
