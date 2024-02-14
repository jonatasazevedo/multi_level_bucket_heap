#!/usr/bin/env bash

make
. set_enviroment.bash
path="out"
g++ "$path"/process.cpp -o "$path"/pcs
./"$path"/run_dataset.sh ${1} ${2} > "$path"/in
./"$path"/pcs < "$path"/in > "$path"/out-k=${1}-t=${2}.csv ${1} ${2}  

# rm "$path"/in
rm "$path"/pcs