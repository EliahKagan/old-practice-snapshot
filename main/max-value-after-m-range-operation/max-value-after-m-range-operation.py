#!/usr/bin/env python3

from itertools import accumulate

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    n, m = read_record()
    deltas = [0] * (n + 1)

    for _ in range(m):
        a, b, k = read_record()
        deltas[a] += k
        deltas[b + 1] -= k

    print(max(accumulate(deltas)))
