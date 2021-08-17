#!/usr/bin/env python3

import collections

def longest(text, max_freq):
    freqs = collections.Counter()
    length = 0

    left = -1
    for right, ch in enumerate(text):
        freqs[ch] += 1

        while freqs[ch] > max_freq:
            left += 1
            freqs[text[left]] -= 1

        length = max(length, right - left)

    return length

def getval():
    return int(input())

for _ in range(getval()):
    max_freq = getval()
    text = input().strip()
    print(longest(text, max_freq))
