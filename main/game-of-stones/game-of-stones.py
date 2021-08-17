#!/usr/bin/env python3

import functools

DELTAS = (2, 3, 5)

@functools.lru_cache(maxsize=None)
def winnable(n):
    return any(delta <= n and not winnable(n - delta) for delta in DELTAS)

def read_value():
    return int(input())

for _ in range(read_value()):
    print('First' if winnable(read_value()) else 'Second')
