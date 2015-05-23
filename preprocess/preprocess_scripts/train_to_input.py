import sys

wordvec = dict()

with open('../word_vectors_files/WORDVEC.TXT', 'r') as f1:
    for line in f1:
        s = line.rstrip().split()
        wordvec[s[0]] = s[1:]

f2 = open('../preprocessed_files/RAW_TRAIN_INPUT.TXT','r')
f3 = open('../../input_files/TRAIN_INPUT.TXT','w')

data_num = 0
f3.write('data_num:   \n')
f3.write('0' + '\n')
f3.write('--------\n')

for line in f2:
    words = line.rstrip().split()

    row_num = len(words)
    '''
    if row_num <= 5:
        continue
    '''
    f3.write('Row: \n' + str(row_num) + '\n')
    f3.write('Col: \n'+  '200\n' + '-----' '\n')
    for word in words:
        s = ' '.join(wordvec[word])
        f3.write(s+"\n")
    f3.write('-----\n')
    data_num += 1


f3.seek(0,0)
f3.write('data_num: \n')
f3.write(str(data_num ) + '\n')
