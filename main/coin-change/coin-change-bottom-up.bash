#!/usr/bin/env bash
# https://www.hackerrank.com/challenges/coin-change/problem in Bash (bottom up)
set -f

declare -ai total_and_len
read -ra total_and_len
declare -ri total="${total_and_len[0]}" len="${total_and_len[1]}"
unset total_and_len

declare -ai coins
read -ra coins

if ((${#coins[@]} != len)); then
    printf '%s: error: wrong record length' "$0" >&2
    exit 1
fi

declare -ai ways=(1)
declare -i subtot coin

for ((subtot = 1; subtot <= total; ++subtot)); do
    ways+=(0)
done

for coin in "${coins[@]}"; do
    for ((subtot = coin; subtot <= total; ++subtot)); do
        ((ways[subtot] += ways[subtot - coin]))
    done
done

printf '%d\n' "${ways[total]}"
