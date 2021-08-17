#!/usr/bin/env bash
# https://www.hackerrank.com/challenges/coin-change/problem in Bash.
# This script requires Bash 4.3, as it uses the [[ -v arr[key] ]] syntax.
set -f

validate_record_length() {
    local -n record="$1"
    local -i length="$2"

    if ((${#record[@]} != length)); then
        printf '%s: error: wrong record length' "$0" >&2
        exit 1
    fi
}

copy_to_assoc() {
    local -n source="$1"
    local -i length="$2"
    local -n target="$3"

    local -i index
    for ((index = 0; index < length; ++index)); do
        ((target["$index"] = source[index]))
    done
}

# read total and len
declare -a total_len_record
read -ra total_len_record
validate_record_length total_len_record 2
declare -ri total="${total_len_record[0]}" len="${total_len_record[1]}"
unset total_len_record

# read coins
declare -a coins_record
read -ra coins_record
validate_record_length coins_record "$len"
declare -Ai coins
copy_to_assoc coins_record "$len" coins
unset coins_record

declare -Ai memo

count_ways() {
    local -ri index="$1" subtotal="$2"
    local -r key="$index $subtotal"
    [[ -v memo["$key"] ]] && return

    if ((subtotal == 0)); then
        ((memo["$key"] = 1))
    elif ((index == len)); then
        ((memo["$key"] = 0))
    else
        local -ri coin="${coins["$index"]}" next_index="$((index + 1))"
        local -i next_subtotal="$subtotal" result=0

        while ((next_subtotal >= 0)); do
            count_ways "$next_index" "$next_subtotal"
            ((result += memo["$next_index $next_subtotal"]))
            ((next_subtotal -= coin))
        done

        ((memo["$key"] = result))
    fi
}

count_ways 0 "$total"
printf '%d\n' "${memo["0 $total"]}"
