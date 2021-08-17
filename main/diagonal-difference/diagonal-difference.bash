#!/usr/bin/env bash

declare -i n=0 d=0 i
read -r n
mapfile -tn $n

for ((i = 0; i < n; ++i)); do
    declare -a row=(${MAPFILE[$i]})
    ((d += row[i] - row[n - i - 1]))
done

echo $((d < 0 ? -d : d))
