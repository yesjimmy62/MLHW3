../word2vec/word2vec -train ../preprocessed_files/RAW_WORDVEC.TXT -output ../word_vectors_files/WORDVEC.TXT -size 200 -window 5    -sample 1e-4 -negative 5 -hs 0 -binary 0 -cbow 1 -iter 3 -min-count 0

