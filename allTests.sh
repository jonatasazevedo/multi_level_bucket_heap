#!/usr/bin/env bash

make
. set_enviroment.bash
path="out"
g++ "$path"/process.cpp -o "$path"/pcs

for ((k=1;k<=${1};k++))
do 
    for ((t=1;t<=${2};t++))
    do
        ./"$path"/run_dataset.sh $k $t > "$path"/in
        ./"$path"/pcs < "$path"/in > "$path"/out-k=$k-t=$t.csv $k $t  
    done 
done

rm "$path"/in
rm "$path"/pcs

