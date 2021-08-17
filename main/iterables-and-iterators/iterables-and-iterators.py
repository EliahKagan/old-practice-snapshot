#!/usr/bin/env python3

from itertools import combinations
from math import factorial

def binom(n, k):
    return factorial(n) // factorial(k) // factorial(n - k)

KEY = 'a'

n = int(input())
a = input().split()
k = int(input())

cnt = sum(1 for pair in combinations(a, k) if KEY in pair)
print('{0:.12f}'.format(cnt / binom(n, k)))
