#!/bin/bash

echo "Test one:
Correct answer: 
ok
My asnwer:"
./script.sh
if [ -n "$suffix" ]; then
    touch a
    diff output.txt answer.txt > a

    if [[ -s a ]]; then
    echo -e "Wrong answer\n"
    else
    echo -e "Оk\n"
    fi
else
    echo -e "The user did not enter the suffix\n"
fi
rm -r output.txt


