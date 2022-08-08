#!/bin/bash

if [[ $1 == "help" ]]
then 
    echo "Введите суффикс"
fi
suffix=$1

lses=`ls`
for file in $lses
do
    if [[ "$file" == *"$suffix"* ]];
    then 
        end=${file##*"$suffix"}
        begin=${file%"$suffix"*}
        end1="$suffix$begin$end"
        end2=${end1##*.}
        end3=${end1%.*}
        echo $end2$end3 >> output.txt
    fi
done