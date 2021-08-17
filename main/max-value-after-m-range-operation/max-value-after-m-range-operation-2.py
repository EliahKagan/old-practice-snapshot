#!/usr/bin/env python3

from itertools import accumulate

def read_fields():
    while True:
        for field in map(int, input().split()):
            yield field

fields = read_fields()

for _ in range(next(fields)):
    deltas = [0] * (next(fields) + 1)

    for _ in range(next(fields)):
        a = next(fields)
        b = next(fields)
        k = next(fields)

        deltas[a] += k
        deltas[b + 1] -= k

    print(max(accumulate(deltas)))
