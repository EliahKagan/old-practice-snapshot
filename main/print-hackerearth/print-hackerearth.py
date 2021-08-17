#!/usr/bin/env python3

from collections import Counter
import itertools

def count_unordered_matches(text, pattern):
    ct = Counter(text)
    cp = Counter(pattern)

    for i in itertools.count():
        for c, k in cp.items():
            ct[c] -= k
            if ct[c] < 0:
                return i

input() # don't need n
print(count_unordered_matches(input(), 'hackerearth'))
