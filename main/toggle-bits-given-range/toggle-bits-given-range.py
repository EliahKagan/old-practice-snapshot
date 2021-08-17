#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def get_mask(size):
    return (1 << size) - 1

def flip_bit_range(n, low, high):
    return get_mask(high) ^ get_mask(low - 1) ^ n # 1-based indexing

for _ in range(int(input())):
    print(flip_bit_range(*read_record()))
