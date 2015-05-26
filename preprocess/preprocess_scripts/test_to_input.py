import sys

wordvecs = dict()
f1 = open('../word_vectors_files/WORDVEC.TXT','r')

count = 0
for line in f1.readlines():
    s = line.rstrip().split()
    word = s[0]
    wordvecString = s[1:]
    wordvecs[word] = wordvecString

f2 = open('../preprocessed_files/RAW_TEST_INPUT_WITH_BRACKET.TXT','r')
f3 = open('../../input_files/TEST_INPUT.TXT','w')
f4 = open('../../input_files/TEST_INPUT_ANS.TXT','w')

option_num = 0
ans_wordvec  = dict()
sentence_wordvec = dict()
ans_pos = 0
wordvec_len = 200
data_num = 0

f3.write('data_num: \n')
f3.write('0' +  '\n')
f3.write('---------\n')

f4.write('data_num: \n')
f4.write('0' + '\n')
f4.write('---------\n')

for line in f2.readlines():
    s  = line.rstrip().split()
    if option_num == 0:
        ans_pos = 0
        sentence_wordvec = {}
        ans_wordvec = {}

        pos = 0
        for w in s:
            if w.startswith('['):
                ans_pos = pos
                if w[1:-1] in wordvec.keys():
                    ans_wordvec[option_num] = wordvecs[w[1:-1]]
                else:
                    ans_wordvec[option_num] = ["0.0"]*200
                pos = pos + 1
            else:
                if w in wordvec.keys():
                    sentence_wordvec[pos] = wordvecs[w]
                else:
                    sentence_wordvec[pos] = ["0.0"]*200
                pos = pos + 1
        option_num += 1
    else:
        w = s[ans_pos]
        if w[1:-1] in wordvecs.keys():
            ans_wordvec[option_num] =  wordvecs[w[1:-1]]
        else:
            z = [str(0.)]*200
            ans_wordvec[option_num] = ' '.join(z)

        if option_num == 4:

            f3.write('row: \n' + str(len(sentence_wordvec)) + '\n' )
            f3.write('col: \n' + str(wordvec_len)+'\n')
            f3.write('ans_pos: \n')
            f3.write(str(ans_pos) + '\n')
            f3.write('------\n')
            for v in sentence_wordvec.values():
                f3.write(' '.join(v) + '\n' )
            f3.write('-----' + '\n')


            f4.write('row: \n' + str(5) + '\n' )
            f4.write('col: \n' + str(wordvec_len) + '\n')
            f4.write('-----\n')
            for v in ans_wordvec.values():
                f4.write(' '.join(v) + '\n' )
            f4.write('-----' + '\n')
            data_num  += 1
            option_num = 0
        else:
            option_num += 1

f3.seek(0,0)
f4.seek(0,0)
f3.write('data_num: \n')
f3.write(str(data_num) + '\n')
f4.write('data_num: \n')
f4.write(str(data_num) + '\n')
