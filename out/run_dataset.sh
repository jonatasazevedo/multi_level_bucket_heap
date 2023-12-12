#!/usr/bin/env bash


path="datasets"

find "$path" -type f -print | sort | while read -r arquivo;
    do
        echo "$(basename $arquivo)"
        > "config"
        printf "dataset=/home/jonatas/Documents/multi_level_bucket_heap/datasets/"$(basename $arquivo)"\nquery=/home/jonatas/Documents/multi_level_bucket_heap/queries/"$(basename $arquivo)"\ntype=main_time"> "config"
            ./build/bin/dijkstra
            ./build/bin/rdijkstra
            ./build/bin/rdijkstra-v2
            ./build/bin/rauction
            ./build/bin/rauction-v2
    done

