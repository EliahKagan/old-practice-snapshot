#!/usr/bin/env python3

from itertools import accumulate

def read_record():
    input() # don't need n
    return list(map(int, input().split()))

def get_first_pivot(a, none=None):
    if len(a) < 2:
        return none if len(a) == 0 else a[0]

    max_ltr = list(accumulate(a, max))
    min_rtl = list(reversed(list(accumulate(reversed(a), min))))

    if a[0] < min_rtl[1]:
        return a[0]

    for i in range(1, len(a) - 1):
        if max_ltr[i - 1] < a[i] < min_rtl[i + 1]:
            return a[i]

    return a[-1] if max_ltr[-2] < a[-1] else none

for _ in range(int(input())):
    print(get_first_pivot(read_record(), none=-1))
