#!/usr/bin/env python3

def popcount(n):
    return sum(int(d) for d in bin(n)[2:])

def count_zeros_in_range(n, right, left):
    if left < right:
        return 0

    ones = popcount(n >> (right - 1)) - popcount(n >> left)
    bits = left - right + 1
    return bits - ones

for _ in range(int(input())):
    print(count_zeros_in_range(*map(int, input().split())))
