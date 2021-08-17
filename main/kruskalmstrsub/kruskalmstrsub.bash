#!/usr/bin/env bash
set -f # shouldn't make a difference, but we don't need or want any globbing

# Array that stores all information for our disjoint set union data structure.
# This is an associative array rather than an indexed array because indexed
# arrays in Bash are actually doubly linked lists and lack O(1) random access.
declare -Ai elems

# Performs $1 makeset operations, with element values 1 through $1.
makesets() {
    declare -i size="$1" i
    for ((i = 1; i <= size; ++i)) do
        ((elems["$i"] = -1))
    done
}

# Advances the variable named as $1 to its value's representative element.
findset() {
    local -n vertex="$1"

    # find the ancestor
    local -i leader="$vertex"
    while ((elems["$leader"] >= 0)); do
        ((leader = elems["$leader"]))
    done

    # compress the path
    local -i follower="$vertex" parent
    while ((follower != leader)); do
        ((parent = elems["$follower"]))
        ((elems["$follower"] = leader))
        ((follower = parent))
    done

    ((vertex = leader))
}

# If the elements passed as $1 and $2 are in different sets, unites those sets
# and returns 0 (true). Otherwise, performs no action and returns 1 (false).
union() {
    # find the ancestors and stop if they are already the same
    local -i i="$1" j="$2"
    findset i
    findset j
    ((i == j)) && return 1

    # unite by rank
    if ((elems["$i"] > elems["$j"])); then
        # j has superior (more negative) rank, so we attach i to it as a branch
        ((elems["$i"] = j))
    else
        # if i and j have the same rank, promote i
        ((elems["$i"] == elems["$j"] && --elems["$i"]))

        # i has superior (more negative) rank, so we attach j to it as a branch
        ((elems["$j"] = i))
    fi

    return 0
}

declare -i vertex_count edge_count
read -r vertex_count edge_count
makesets "$vertex_count"

declare -i u v w sum=0
while read -r u v w; do
    union "$u" "$v" && ((sum += w))
done < <(head -n "$edge_count" | sort -bnsk3)

printf '%d\n' "$sum"
