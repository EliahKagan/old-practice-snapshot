#!/usr/bin/env python3

import collections

class OrderedCounter(collections.Counter, collections.OrderedDict):
    pass

NO_ELEMENT = -1

def first_with_freq(a, k):
    '''Of elements of an iterable, a, that occur at least k times, returns the
    first ever to occur, or NO_ELEMENT if nothing occurs at least k times.'''
    for val, freq in OrderedCounter(a).items():
        if freq == k:
            return val

    return NO_ELEMENT

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    n, k = read_record()
    a = read_record()
    print(NO_ELEMENT if n < k else first_with_freq(a, k))
