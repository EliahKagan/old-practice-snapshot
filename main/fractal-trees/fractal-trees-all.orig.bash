#!/usr/bin/env bash

declare -A a=()
declare -r fg=1 # foreground character
declare -r bg=_ # background character

draw() {
    local -i  x=$1  # most recently drawn-to column number, rightward from 0
    local -i  y=$2  # most recently drawn-to row number, upward from 0
    local -ri d=$3  # vertical displacement of trunk, then again of branch
    local -ri n=$4  # number of iterations remaining, including this one

    ((n > 0)) || return

    local -i i

    for ((i = d; i > 0; --i)); do
        ((++y))
        a["$x,$y"]=$fg
    done

    local -i x_=$x y_=$y

    for ((i = d; i > 0; --i)); do
        ((++y_, --x_))
        a["$x_,$y_"]=$fg
    done

    draw $x_ $y_ $((d / 2)) $((n - 1))

    for ((i = d; i > 0; --i)); do
        ((++y, ++x))
        a["$x,$y"]=$fg
    done

    draw $x $y $((d / 2)) $((n - 1))
}

declare -i n=0
read -r n
draw 49 -1 16 $n

declare -i x y

for ((y = 62; y >= 0; --y)); do
    for ((x = 0; x < 100; ++x)); do
        printf %c ${a["$x,$y"]:-$bg}
    done

    printf \\n
done
