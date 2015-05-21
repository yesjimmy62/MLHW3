import sys

f = open("TRAIN_INPUT.TXT",'r')

line = 1
max_num = 0
while line:
    line = f.readline()
    words = line.rstrip().split()
    if  len(words) > max_num:
        max_num = len(words)

print "Max_NUM : %d"%(max_num)
