#!/usr/bin/env python3

import itertools

def read_squares_mod(m):
    '''Returns values congruent mod m to the squares of input values.'''
    _, *tokens = input().split()
    
    for s in tokens:
        # Only congruence is required and m <= 1000, so I mod before squaring
        # (and not again afterwards) to maximize speed.
        x = int(s) % m
        yield x * x

k, m = map(int, input().split())
rows = (list(read_squares_mod(m)) for _ in range(k))
combos = itertools.product(*rows)
print(max(sum(c) % m for c in combos))
