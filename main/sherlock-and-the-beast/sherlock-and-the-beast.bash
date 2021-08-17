#!/usr/bin/env bash

declare -i t=0 i n=0 fives threes
declare max_decent

read -r t

for i in $(seq 1 $t); do
    max_decent=-1
    read -r n

    for ((fives = n; fives >= 0; --fives)); do
        ((threes = n - fives))

        if ((fives % 3 == 0 && threes % 5 == 0)); then
            max_decent="$(printf '%*s' $fives '' | tr ' ' 5)"
            max_decent+="$(printf '%*s' $threes '' | tr ' ' 3)"
            break
        fi
    done

    echo "$max_decent"
done
