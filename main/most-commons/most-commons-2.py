#!/usr/bin/env python3

from collections import Counter

pairs = sorted(Counter(input().strip()).items(),
               key=lambda kv: (-kv[1], kv[0]))

for kv in pairs[:3]:
    print(*kv)
