#!/usr/bin/env python3

from collections import Counter

def process_names(names):
    counts = Counter()
    for name in names:
        old_count = counts[name]
        counts[name] = old_count + 1
        yield 'Verified' if old_count == 0 else name + str(old_count)

for _ in range(int(input())):
    input() # don't need n
    print(*process_names(input().split()))
