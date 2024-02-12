#!/usr/bin/env bash


path="datasets"

find "$path" -type f -print | sort | while read -r arquivo;
    do
        echo "$(basename $arquivo)"
        > "config"
        printf "dataset=/home/jonatas/Documents/multi_level_bucket_heap/datasets/"$(basename $arquivo)"\nquery=/home/jonatas/Documents/multi_level_bucket_heap/queries/"$(basename $arquivo)"\ntype=main_time"> "config"
            for i in {1..10}
            do 
                ./build/bin/dijkstra 
            done
            for i in {1..10}
            do 
                ./build/bin/rdijkstra 
            done
            for i in {1..10}
            do 
                ./build/bin/rdijkstra-v2 
            done
            for i in {1..10}
            do 
                ./build/bin/rauction 
            done
            for i in {1..10}
            do 
                ./build/bin/rauction-v2 
            done
    done

