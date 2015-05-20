import sys

wordvect = dict()

with open('../word_vectors_files/WORD_VECT.TXT', 'r') as f1:
    for line in f1:
        s = line.rstrip().split()
        wordvect[s[0]] = s[1:]

f2 = open('../preprocessed_files/RAW_TRAIN_INPUT.TXT','r')
f3 = open('../preprocessed_files/TRAIN_INPUT.TXT','w')

num_of_data = 0
for line in f2:
    words = line.rstrip().split()
    row_num = len(word)
    if row_num <= 5:
        continue
    f3.write("Row:\n"+str(row_num)+"\n")
    f3.write("Col:\n200\n-----\n")
    for word in words:
        f3.write(wordvect[word]+"\n")




