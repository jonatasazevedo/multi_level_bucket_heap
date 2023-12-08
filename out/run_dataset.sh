#!/usr/bin/env bash


path="datasets"

find "$path" -type f -exec sh -c '
    for arquivo; do
        echo "Arquivo: $(basename $arquivo)"
        > "config"
        echo 
        printf "dataset=/home/jonatas/Documents/multi_level_bucket_heap/datasets/"$(basename $arquivo)"\nquery=/home/jonatas/Documents/multi_level_bucket_heap/queries/"$(basename $arquivo)"\ntype=check_sum"> "config"
            ./build/bin/dijkstra
            ./build/bin/rdijkstra
            ./build/bin/rdijkstra-v2
            ./build/bin/rauction
            ./build/bin/rauction-v2
    done
' sh {} +

