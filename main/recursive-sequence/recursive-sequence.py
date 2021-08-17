#!/usr/bin/env python3

from functools import reduce
from operator import mul

def read_val():
    return int(input())

def compute_sequence(nmax):
    acc = 0
    cur = 1

    for i in range(1, nmax + 1):
        nxt = cur + i
        acc += reduce(mul, range(cur, nxt))
        yield acc
        cur = nxt

NMAX = 10
SEQ = list(compute_sequence(NMAX))

for _ in range(read_val()):
    print(SEQ[read_val() - 1])
