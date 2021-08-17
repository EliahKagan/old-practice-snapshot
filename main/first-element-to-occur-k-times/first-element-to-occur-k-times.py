#!/usr/bin/env python3

from collections import Counter

NO_ELEMENT = -1

def read_record():
    return map(int, input().split())

def first_with_freq(a, k):
    '''Of elements of a list, a, that occur at least k times, returns the first
    ever to occur. Returns NO_ELEMENT if nothing occurs at least k times.'''
    c = Counter(a)
    for x in a:
        if c[x] == k:
            return x

    return NO_ELEMENT

for _ in range(int(input())):
    n, k = read_record()
    values = read_record()
    print(NO_ELEMENT if n < k else first_with_freq(list(values), k))
