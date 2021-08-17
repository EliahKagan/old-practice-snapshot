#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def has_range(elems, low, high):
    return len(set(x for x in elems if low <= x <= high)) == high - low + 1

for _ in range(int(input())):
    _, low, high = read_record() # don't need n
    print('Yes' if has_range(read_record(), low, high) else 'No')
