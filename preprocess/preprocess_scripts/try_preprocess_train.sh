#!/bin/bash -e
cat ../../../Holmes_Training_Data/*.TXT | sed "s///g" \
| tr '[:upper:]' '[:lower:]' \
| sed "/.txt/d" \
| sed "/^$/d" \
| sed "/\@./d" \
| sed "/login:/d" \
| sed "/password:/d" \
| sed "/ftp/d" \
| sed "/---/d" \
| sed "/xx/d" \
| tr '\n' ' ' \
| sed "s/.*\*end\*//g" \
| sed "s/#/ /g" \
| sed "s/:/ /g" \
| sed "s/\[.*\]/ /g" \
| sed "s/(.*)//g" \
| sed "s/<.*>/ /g" \
| sed "s/\.+/\./g" \
| sed "s/\"//g" \
| sed "s/-//g" \
| sed "s/_//g" \
| sed "s/[^[:print:]]//g" \
| sed "s/mr./mr/g" \
| sed "s/j.[ \t]*p/jp/g" \
| sed "s/mrs./mrs/g" \
| sed "s/st./st/g" \
| sed "s/dr./dr/g" \
| sed "s/i'm/i am/g" \
| sed "s/he's/he is/g" \
| sed "s/she's/she is/g" \
| sed "s/they're/they are/g" \
| sed "s/'d/ would/g" \
| sed "s/'ve/ have/g" \
| sed "s/ ah / /g" \
| sed "s/don't/do not/g" \
| sed "s/'ll/ will/g" \
| sed "s/'re/ are/g" \
| sed "s/'in/ing/g" \
| sed "s/didn't/did not/g" \
| sed "s/'/ /g" \
| sed "s/\./ \.\n/g" \
| sed "/\*/d" \
| sed "s/;/ \n/g" \
| sed "s/\?/ \n/g" \
| sed "s/!/ \n/g" \
| sed "s/[ \t]+/ /g" \
| sed "s/^[ \t]*//g" \
| sed "s/^but,*//g" \
| sed "s/^and,*//g" \
| sed "s/^so,*//g" \
| sed "s/^then,*//g" \
| sed "s/^[ \t]*//g" \
| sed "/^said/d" \
| sed "s/,/ ,/g"              >  TRY_TRAIN_INPUT.TXT
