import sys
import random

wordvec = dict()

with open('../word_vectors_files/WORDVEC_len1.TXT', 'r') as f1:
    for line in f1:
        s = line.rstrip().split()
        wordvec[s[0]] = s[1:]

f2 = open('../preprocessed_files/TRAIN.TXT','r')
f3 = open('../../input_files/TRAIN_INPUT.TXT','w')

data_num = 0
f3.write('data_num:   \n')
f3.write('0' + '\n')
f3.write('--------\n')


for line in f2:

    words = line.rstrip().split()
    if len(words) <10 or len(words) >40:
        continue
    k = random.random()
    if k > 0.035:
        continue

    row_num = len(words)
    f3.write('Row: \n' + str(row_num) + '\n')
    f3.write('Col: \n'+  '200\n' + '-----' '\n')
    for word in words:
        s = ""
        try:
            s=' '.join(wordvec[word])
        except KeyError:
            s = ' '.join(["0.00000"]*200)

        f3.write(s+'\n')

    f3.write('-----\n')
    print "Writing Sentence " + str(data_num) + " Done \n"
    data_num += 1


f3.seek(0,0)
f3.write('data_num: \n')
f3.write(str(data_num)+'\n')
