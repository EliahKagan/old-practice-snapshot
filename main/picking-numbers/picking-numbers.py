#!/usr/bin/env python3

from collections import Counter

input() # don't need n
counts = Counter(map(int, input().split()))
print(max(counts[key] + counts[key + 1] for key in counts.keys()))
