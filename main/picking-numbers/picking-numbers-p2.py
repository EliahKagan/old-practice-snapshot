#!/usr/bin/env python

from collections import Counter

raw_input() # don't need n
counts = Counter(map(int, raw_input().split()))
print max(counts[key] + counts[key + 1] for key in counts.keys())
