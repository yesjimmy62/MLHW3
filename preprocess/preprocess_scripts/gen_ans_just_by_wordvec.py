import sys
import re
import numpy as np
from  numpy.linalg import norm

wordvecs = dict()

with open('../word_vectors_files/WORDVEC.TXT','r') as f1:
    for line in f1:
        s = line.strip().split()
        f_array = map(float,s[1:])
        wordvecs[s[0]] = np.array(f_array)

f2 = open('../preprocessed_files/RAW_TEST_INPUT_WITH_BRACKET.TXT')
f3 = open('../guess2.CSV','w')
f3.write("Id,Answer\n")

line = 1
sentence_num = 0

while line:
    if sentence_num == 1040:
        break

    ss = []
    for i in range(5):
        s = f2.readline()
        ss.append(s.rstrip().split())

    ans_pos = 0
    pos = 0
    for w in ss[0]:
        if w.startswith('['):
            ans_pos = pos
        pos = pos + 1

    ans_wordvecs = dict()
    s_without_ans_wordvecs = dict()

    for i in range(5):
        w = ss[i][ans_pos][1:-1]
        ans_wordvecs[i] = wordvecs[w]

    for i in range(len(ss[0])):
        if i == ans_pos:
            continue
        w = ss[0][i]
        s_without_ans_wordvecs[i] = wordvecs[w]

    ans_score = dict()

    for i in range(5):
        score = 0
        for vec in s_without_ans_wordvecs.values():
            score += np.dot(vec,ans_wordvecs[i])/(norm(vec)*norm(ans_wordvecs[i]))
        ans_score[i] = score

    qq = {0:'a',1:'b',2:'c',3:'d',4:'e'}
    a = 0
    m = 0

    for i in range(5):
        temp = ans_score[i]
        if temp > m:
            m = temp
            a = i

    f3.write(str(sentence_num+1)+","+qq[a]+"\n")
    sentence_num += 1

