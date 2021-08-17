#!/usr/bin/env python3

from math import factorial

MOD = 10**9 + 7

def compute_path_count(n, m):
    return factorial(n + m) // factorial(n) // factorial(m)

for _ in range(int(input())):
    n, m = map(int, input().split())
    print(compute_path_count(n - 1, m - 1) % MOD)
