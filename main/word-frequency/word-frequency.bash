#!/bin/bash
set -f

infile='words.txt'
declare -Ai freq

while read -r; do
    for word in $REPLY; do
         ((++freq["$word"]))
    done
done <"$infile"

for word in "${!freq[@]}"; do
    printf '%s %d\n' "$word" "${freq["$word"]}"
done | sort -nrk2
