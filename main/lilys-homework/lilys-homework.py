#!/usr/bin/env pypy3

import itertools

VISITED = -1

def normalize_to_permutation(values, reverse):
    return sorted(range(len(values)), reverse=reverse, key=lambda i: values[i])

def traverse_and_mark_cycle(permutation, start):
    '''Traverses the cycle of the permutation that begins at the index start,
    marking each element visited and returning the number of positions
    traversed (always at least 1).'''
    i = start
    for cycle_length in itertools.count(1):
        permutation[i], i = VISITED, permutation[i] # advance to next value
        if i == start:
            return cycle_length

def compute_min_swaps(values, reverse):
    permutation = normalize_to_permutation(values, reverse)

    swaps = 0
    for i in range(len(permutation)):
        if permutation[i] != VISITED:
            swaps += traverse_and_mark_cycle(permutation, i) - 1

    return swaps

input() # don't need n
values = list(map(int, input().split()))

print(min(compute_min_swaps(values, False), compute_min_swaps(values, True)))
