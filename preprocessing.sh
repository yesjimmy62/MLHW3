#!/bin/bash -e
cat ../Holmes_Training_Data/*.TXT | sed "s///g" \
| tr '[:upper:]' '[:lower:]' \
| sed '/.txt/d' \
| sed '/\*\*/d' \
| sed '/^$/d' \
| sed '/\@.*.com/d' \
| sed '/login:/d' \
| sed '/password:/d' \
| sed '/ftp/d' \
| sed '/---/d' \
| tr '\n' ' ' \
| sed "s/#//g" \
| sed "s/  / /g" \
| sed 's/\*//g' \
| sed 's/\[.*\]//g' \
| sed 's/(.*)//g' \
| sed "s/<.*>//g" \
| sed 's/\.\.\.*/\./g' \
| sed "s/\t/ /g" \
| sed "s/i'm/i am/g" \
| sed "s/he's/he is/g" \
| sed "s/she's/she is/g" \
| sed "s/they're/they are/g" \
| sed "s/i'd/i would/g" \
| sed "s/he'd/he would/g" \
| sed "s/she'd/she would/g" \
| sed "s/i've/i have/g" \
| sed "s/they've/they have/g"  > TRAIN.TXT
