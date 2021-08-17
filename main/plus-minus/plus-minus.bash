#!/usr/bin/env bash

declare -i n=0 k zero=0 neg=0 pos=0 tot
declare -ai a=()

read -r n
read -ra a

for k in ${a[*]:0:$n}; do
    ((k == 0 ? ++zero : (k < 0 ? ++neg : ++pos)))
done
((tot = zero + neg + pos))

for k in $pos $neg $zero; do
    printf '%.6f\n' "$(bc -l <<<"$k/$tot")"
done
