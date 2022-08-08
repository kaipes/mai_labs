#!/bin/bash

touch f1.txt
touch f2.txt
touch f3.txt
touch output.txt
touch answer.txt
echo txtanswer >> answer.txt
echo txtf1 >> answer.txt
echo txtf2 >> answer.txt
echo txtf3 >> answer.txt
echo txtoutput >> answer.txt
./script.sh tyt
echo "Test third:
Correct answer: 
ok
My answer:"
touch a
diff output.txt answer.txt > a
if [[ -s a ]]; then
echo -e "Not exist files with suffix\n"
else
echo -e "Ok\n"
fi
rm -r f1.txt f2.txt f3.txt output.txt answer.txt a