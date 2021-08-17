#!/usr/bin/env python3

from fractions import gcd
from functools import reduce

def read_record():
    return map(int, input().split())

def gcd_list(nums):
    return reduce(gcd, sorted(nums))

for _ in range(int(input())):
    input() # don't need n
    print('YES' if gcd_list(read_record()) == 1 else 'NO')
