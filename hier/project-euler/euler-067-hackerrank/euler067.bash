#!/usr/bin/env bash
set -f

declare -i size
declare -Ai grid

read_row() {
    local -i row_idx="$1" col_idx=0 elem
    local line
    IFS= read -r line

    for elem in $line; do
        ((grid["$row_idx $((col_idx++))"] = elem))
    done
}

read_grid() { # replaces size and grid with new value, read from stdin
    read -r size
    grid=()

    local -i row_idx
    for ((row_idx = 0; row_idx < size; ++row_idx)); do
        read_row "$row_idx"
    done
}

tabulate_row() {
    local -i row_idx="$1" prev_row_idx="$((row_idx - 1))"

    # accumulate the only available "choices" into the two edge cells
    ((grid["$row_idx 0"] += grid["$prev_row_idx 0"]))
    ((grid["$row_idx $row_idx"] += grid["$prev_row_idx $prev_row_idx"]))

    # accumulate the best of the two real choices into all non-edge cells
    local -i col_idx left right
    for ((col_idx = 1; col_idx < row_idx; ++col_idx)); do
        ((left = grid["$prev_row_idx $((col_idx - 1))"]))
        ((right = grid["$prev_row_idx $col_idx"]))
        ((grid["$row_idx $col_idx"] += (left > right ? left : right)))
    done
}

tabulate_grid() {
    local -i row_idx
    for ((row_idx = 1; row_idx < size; ++row_idx)); do
        tabulate_row "$row_idx"
    done
}

print_best() {
    local -i best=0 cur row_idx="$((size - 1))" col_idx

    for ((col_idx = 0; col_idx <= row_idx; ++col_idx)); do
        ((cur = grid["$row_idx $col_idx"]))
        ((best < cur)) && ((best = cur))
    done

    printf '%d\n' "$best"
}

declare -i t=0
read -r t

while ((t-- > 0)); do
    read_grid
    tabulate_grid
    print_best
done
