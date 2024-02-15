#!/usr/bin/env bash

make
. set_enviroment.bash
path="out"
g++ "$path"/process.cpp -o "$path"/pcs

for ((k=1;k<=${1};k++))
do 
    ./"$path"/run_dataset.sh $k > "$path"/in
    ./"$path"/pcs < "$path"/in > "$path"/out-k=$k.csv $k   
done

rm "$path"/in
rm "$path"/pcs

