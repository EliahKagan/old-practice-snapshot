#!/usr/bin/env python3
# This is a generalization of Project Euler problem #2. It is the same
# generalization, with the same input format, as on HackerRank, except that
# the maximum value of N here is smaller (10**6 insteead of 4 * 10**16).
# See https://www.hackerrank.com/contests/projecteuler/challenges/euler002.

from bisect import bisect_right
from itertools import accumulate

def read_val():
    return int(input())

def get_max_less_or_equal(keys, values, search_key):
    return values[bisect_right(keys, search_key) - 1]

def even_fibonacci(bound):
    a = 0
    b = 2

    while a <= bound:
        yield a
        a, b = b, a + b * 4

NMAX = 1000000
SEQ = list(even_fibonacci(NMAX))
SUMS = list(accumulate(SEQ))

for _ in range(read_val()):
    print(get_max_less_or_equal(SEQ, SUMS, read_val()))
