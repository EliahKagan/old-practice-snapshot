#!/usr/bin/env python3

import itertools

def getval():
    return int(input())

def find_first_set_bit(n):
    '1-based index of first bit of n, or 0 if n == 0.'
    if n == 0:
        return 0
    
    for i in itertools.count(1):
        if n & 1:
            return i
        n >>= 1

for _ in range(getval()):
    print(find_first_set_bit(getval()))
