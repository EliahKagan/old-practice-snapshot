#!/usr/bin/env python3

def c_ways(n):
    # (not used) + (used once) + (used twice)
    return 1 + n + n * (n - 1) // 2

def bc_ways(n):
    return n * c_ways(n - 1) + c_ways(n)

def read_value():
    return int(input())

for _ in range(read_value()):
    print(bc_ways(read_value()))
