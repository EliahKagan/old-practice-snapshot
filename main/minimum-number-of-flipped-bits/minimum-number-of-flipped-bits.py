#!/usr/bin/env python3

def read_bits():
    return list(map(int, input().strip()))

def count_flips(bits, start):
    return sum(bit ^ (i % 2) for (i, bit) in enumerate(bits, start))

def get_min_flips(bits):
    return min(count_flips(bits, 0), count_flips(bits, 1))

for _ in range(int(input())):
    print(get_min_flips(read_bits()))
