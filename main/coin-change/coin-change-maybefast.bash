#!/usr/bin/env bash
# https://www.hackerrank.com/challenges/coin-change/problem in Bash.
# This script requires Bash 4.3, as it uses the [[ -v arr[key] ]] syntax.
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

if ((total == 0)); then
    printf '%d\n' 1
    exit 0
fi

if ((len == 0)); then
    printf '%d\n' 0
    exit 0
fi

declare -Ai memo

count_ways() {
    local -ri index="$1" subtotal="$2"
    local -r key="$index $subtotal"
    [[ -v memo["$key"] ]] && return

    local -ri coin="${coins[index]}" next_index="$((index + 1))"

    if ((next_index == len)); then
        ((memo["$key"] = subtotal % coin == 0 ? 1 : 0))
        return
    fi

    local -i next_subtotal="$subtotal" result=0

    while ((next_subtotal > 0)); do
        count_ways "$next_index" "$next_subtotal"
        ((result += memo["$next_index $next_subtotal"]))
        ((next_subtotal -= coin))
    done

    ((next_subtotal == 0)) && ((++result))
    ((memo["$key"] = result))
}

count_ways 0 "$total"
printf '%d\n' "${memo["0 $total"]}"
