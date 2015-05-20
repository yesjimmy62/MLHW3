#!/bin/bash -e
cat ../../../testing_data.txt | sed "s/^.*) //g" \
|tr '[:upper:]' '[:lower:]' >  ../preprocessed_files/RAW_TEST_WITH_BRACKETS.TXT
