#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    input() # don't need n, m
    a = read_record()
    b = frozenset(read_record())
    print(' '.join(str(x) for x in a if x not in b))
