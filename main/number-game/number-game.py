#!/usr/bin/env python3

from itertools import accumulate, chain
from math import gcd

def read_val():
    return int(input())

def lcm(m, n):
    return m // gcd(m, n) * n

def running_lcm(low, high):
    return accumulate(range(low, high + 1), lcm)

NMAX = 30
SEQ = list(chain((None,), running_lcm(1, NMAX)))

for _ in range(read_val()):
    print(SEQ[read_val()])
