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

option_num = 0
ans_wordvec  = dict()
sentence_wordvec = dict()
ans_pos = 0
wordvec_len = 200

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
                ans_wordvec[option_num] = wordvecs[w[1:-1]]
                pos = pos + 1
            else:
                sentence_wordvec[pos] = wordvecs[w]
                pos = pos + 1
        option_num += 1
    else:
        w = s[ans_pos]
        print w
        if w[1:-1] in wordvecs.keys():
            ans_wordvec[option_num] =  wordvecs[w[1:-1]]
        else:
            z = [str(0.)]*200
            ans_wordvec[option_num] = ' '.join(z)

        if option_num == 4:
            f3.write('col: ' + str(wordvec_len)+'\n')
            f3.write('row:' + str(len(sentence_wordvec)) + '\n' )
            f3.write('ans_num:' + '5' + '\n')
            for v in sentence_wordvec.values():
                f3.write(' '.join(v) + '\n' )
            for v in ans_wordvec.values():
                f3.write(' '.join(v) + '\n')
            f3.write('-----' + '\n')
            option_num = 0
        else:
            option_num += 1


