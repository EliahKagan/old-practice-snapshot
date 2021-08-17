#!/usr/bin/env python3

MOD = 10**9 + 7

def read_record():
    input() # don't need length
    return map(int, input().split())

def is_pow_2(n):
    return n & (n - 1) == 0 and n != 0

def count_pow_2(values):
    return sum(1 for n in filter(is_pow_2, values))

for _ in range(int(input())):
    with_empty_set = pow(2, count_pow_2(read_record()), MOD)
    print((with_empty_set - 1) % MOD)
