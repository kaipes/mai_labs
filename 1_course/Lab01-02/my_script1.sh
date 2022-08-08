#!/bin/bash
client=`whoami`
echo 'User: ' $client
echo 'path': `pwd`
rm -rf dir && mkdir dir && cd dir
pushd .
echo 'path_1': `pwd`
echo 'mai1' > f1.txt
echo 'mai2'> f2.txt
ls
cat f1.txt f2.txt >> f3.txt
cat f1.txt >  f2.txt
cat f2.txt
cp f2.txt a1.txt
ls
ls | grep f
ls | xargs -ixxx cat xxx
find f3.txt
mv f3.txt f2.txt
rm a1.txt
ls | xargs -ixxx wc -l xxx
ls | xargs -ixxx mv xxx xxx_pr

rm -rf dir1 && mkdir dir1 
pushd dir1
popd 
popd
rm -rf dir1 && touch b.txt && ls
cd ~

