for i in ../../../Holmes_Training_Data/*.TXT; do
     sed -n '/\*END\*/,$p' $i > temp.txt 
     sed '1d' temp.txt > $i
done 
rm temp.txt
