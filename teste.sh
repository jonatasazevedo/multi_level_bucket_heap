#!/usr/bin/env bash

. set_enviroment.bash

path="datasets"

find "$path" -type f -exec sh -c '
    for arquivo; do
        echo "Arquivo: $(basename $arquivo)"
        > "config"
        printf "dataset=/home/jonatas/Documents/multi_level_bucket_heap/datasets/"$(basename $arquivo)"\nquery=/home/jonatas/Documents/multi_level_bucket_heap/queries/"$arquivo"\ntype=main_time "> "config"
            ./run dijkstra
            ./run rdijkstra
            ./run rdijkstra-v2
            ./run rauction
            ./run rauction-v2
    done
' sh {} +