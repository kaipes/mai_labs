#!/bin/bash
mkdir new
cd new

touch file1.txt file2.txt
tee -a file1.txt << EOF 
Hello world!
Halo people
Hello man
EOF

echo -e "Hello world! \nHello people \nHalo men" > file2.txt
cmp -b file1.txt file2.txt
diff -sb file1.txt file2.txt
wc -c file1.txt
wc -l file1.txt
echo "Hello world !" | awk '{print $3}'
od -c file2.txt
sort file2.txt
echo "-------"
head -2 file2.txt || tail -3 file2.txt
echo -e "type\ndef\ndef\nhorror\ntype" | uniq --group=both
md5sum file1.txt
touch file3.txt
echo -e "100\n103" > file3.txt
od -b file3.txt
cut -b 1,4 file2.txt
dd if=file1.txt of=file2.txt seek=2

grep -c Hello file2.txt
find . -name "*3.txt"
ls | xargs -ixxx rm xxx