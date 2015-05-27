cat  ../preprocessed_files/TRAIN.TXT ../word2vec/text8  > ../preprocessed_files/RAW_WORDVEC.TXT 
../word2vec/word2vec -train ../preprocessed_files/RAW_WORDVEC.TXT -output ../word_vectors_files/WORDVEC_CLASS.TXT -size 200 -window 10 -nagative 25  -sample 1e-4  -hs 0  -cbow 1 -iter 5 -min-count 5 -binary 0 -class 100 
