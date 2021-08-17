#!/usr/bin/env python3

from collections import Counter

pairs = list(Counter(input().strip()).items())
pairs.sort(key=lambda kv: kv[0])
pairs.sort(key=lambda kv: -kv[1])

for kv in pairs[:3]:
    print(*kv)
