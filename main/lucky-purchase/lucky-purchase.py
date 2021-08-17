#!/usr/bin/env python3

from collections import Counter

catalog = {}

for _ in range(int(input())):
    name, price = input().split()
    counts = Counter(map(int, price))
    if 0 < counts[4] == counts[7] and len(counts) == 2:
        catalog[name] = int(price)

print(min(catalog.keys(), default='-1', key=lambda name: catalog[name]))
