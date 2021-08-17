#!/usr/bin/env python3

from bisect import bisect_right
from itertools import accumulate

def read_val():
    return int(input())

def get_max_less_or_equal(a, x):
    return a[bisect_right(a, x) - 1]

def even_fibonacci(bound):
    a = 0
    b = 2

    while a <= bound:
        yield a
        a, b = b, a + b * 4

NMAX = 4 * 10**16
EVEN_FIBONACCI_SUMS = list(accumulate(even_fibonacci(NMAX)))

for _ in range(read_val()):
    print(get_max_less_or_equal(EVEN_FIBONACCI_SUMS, read_val()))
