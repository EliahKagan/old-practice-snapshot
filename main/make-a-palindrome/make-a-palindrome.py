#!/usr/bin/env python3

from collections import Counter

for _ in range(int(input())):
    counts = Counter(input().strip()).values()
    print(max(0, sum(1 for c in counts if c % 2 != 0) - 1))
