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

declare -ai result_stack
declare -Ai memo

count_ways() {
    local -ri index="$1" subtotal="$2"

    if ((subtotal == 0)); then
        result_stack+=(1)
        return
    fi

    if ((index == len)); then
        result_stack+=(0)
        return
    fi

    local -r key="$index $subtotal"

    if [[ -v memo["$key"] ]]; then
        result_stack+=("${memo["$key"]}")
        return
    fi

    local -ri coin="${coins[index]}" next_index="$((index + 1))"
    local -i next_subtotal="$subtotal" result=0

    while ((next_subtotal >= 0)); do
        count_ways "$next_index" "$next_subtotal"
        ((result += result_stack[-1]))
        unset 'result_stack[-1]' # pop
        ((next_subtotal -= coin))
    done

    ((memo["$key"] = result))
    result_stack+=("$result")
}

count_ways 0 "$total"
printf '%d\n' "${result_stack[-1]}"
