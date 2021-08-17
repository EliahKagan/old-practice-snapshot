#!/usr/bin/env python3

from itertools import groupby, islice

for _ in range(int(input())):
    input() # don't need n
    it = map(int, input().split())

    width = 1
    while True:
        row = sorted(islice(it, 0, width))
        if not row:
            break
        print(*(g[0] for g in groupby(row)))
        width *= 2
