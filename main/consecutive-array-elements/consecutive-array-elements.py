#!/usr/bin/env python3

def read_record():
    return list(map(int, input().split()))

def is_consecutive(a):
    return max(a) - min(a) + 1 == len(a) == len(frozenset(a))

for _ in range(int(input())):
    input() # don't need n
    print('Yes' if is_consecutive(read_record()) else 'No')
