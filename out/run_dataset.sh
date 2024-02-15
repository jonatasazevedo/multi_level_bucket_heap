#!/usr/bin/env bash


path="datasets"
find "$path" -type f -print | sort | while read -r arquivo;
    do
        echo "$(basename $arquivo)"
        > "config"
        printf "dataset=/home/jonatas/Documents/multi_level_bucket_heap/datasets/"$(basename $arquivo)"\nquery=/home/jonatas/Documents/multi_level_bucket_heap/queries/"$(basename $arquivo)"\ntype=main_time"> "config"
        ./build/bin/dijkstra ${1} ${2}
    done

