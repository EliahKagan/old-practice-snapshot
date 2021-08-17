#!/usr/bin/env python3

from math import ceil, sqrt

t = int(input())
group = ceil((sqrt(24 * t + 9) - 3) / 6) # group number, using 1-based indexing
offset = 3 * (group - 1) * group // 2    # highest number in previous group
pos = t - offset                         # position in its own group
