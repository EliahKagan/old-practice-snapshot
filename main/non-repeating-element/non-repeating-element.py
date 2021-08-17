#!/usr/bin/env python3

from collections import Counter

for _ in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    c = Counter(a)
    try:
        print(next(x for x in a if c[x] == 1))
    except StopIteration:
        print(0)
