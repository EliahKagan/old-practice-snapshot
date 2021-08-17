#!/usr/bin/env python3


def max_nonadjacent_sum(values):
    """Finds the maximum sum of nonadjacent values."""
    taken = skipped = 0

    for val in values:
        taken, skipped = skipped + val, max(taken, skipped)

    return max(taken, skipped)


def read_record():
    """Reads a line of numbers as an interable of ints."""
    return map(int, input().split())


input()  # don't need n
print(max_nonadjacent_sum(read_record()))
