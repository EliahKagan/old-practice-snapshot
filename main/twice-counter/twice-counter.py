#!/usr/bin/env python3

from collections import Counter

for _ in range(int(input())):
    input() # don't need n
    counts = Counter(input().split()).values()
    print(sum(1 for c in counts if c == 2))
