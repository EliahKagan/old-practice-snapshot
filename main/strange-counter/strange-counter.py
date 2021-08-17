#!/usr/bin/env python3

from math import ceil, log2

t = int(input())
group = ceil(log2(t / 3 + 1)) - 1   # group number, using 0-based indexing
grange = 3 * 2**group               # number of items in the current group
offset = grange - 3                 # highest number in previous group
pos = t - offset                    # position in its own group
print(grange - pos + 1)
