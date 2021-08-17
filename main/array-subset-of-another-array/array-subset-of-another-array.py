#!/usr/bin/env python3

def read_set():
    return frozenset(map(int, input().split()))

for _ in range(int(input())):
    input() # don't need m, n
    a = read_set()
    b = read_set()
    print('Yes' if b <= a else 'No')
