#!/usr/bin/env python3

import collections

for _ in range(int(input())):
    input() # don't need n
    counts = collections.Counter(input().split())
    _, winner = min((-count, name) for name, count in counts.items())
    print(winner)
