#!/usr/bin/env bash

make
. set_enviroment.bash
path="out"
./"$path"/run_dataset.sh > "$path"/in
g++ "$path"/process.cpp -o "$path"/pcs
./"$path"/pcs < "$path"/in > "$path"/out
rm "$path"/in
