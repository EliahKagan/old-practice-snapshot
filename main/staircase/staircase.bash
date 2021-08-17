#!/usr/bin/env bash

declare -i n=0 i
read -r n

for i in $(seq 1 $n); do
    printf '%*s\n' $n "$(printf '%*s' $i '' | tr ' ' '#')"
done
