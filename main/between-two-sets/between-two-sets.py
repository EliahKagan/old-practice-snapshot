#!/usr/bin/env python3

from functools import reduce
from math import gcd

def lcm(m, n):
    return m // gcd(m, n) * n

def get_record():
    return map(int, input().split())

def get_bound(reducer):
    return reduce(reducer, sorted(get_record()))

input() # don't need n, m
lower = get_bound(lcm)
upper = get_bound(gcd)

multiples = range(lower, upper + 1, lower)
print(sum(1 for multiple in multiples if upper % multiple == 0))
