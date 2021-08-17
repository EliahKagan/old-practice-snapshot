#!/usr/bin/env python3

def read_record():
    input() # don't need n
    return map(int, input().split())

def alternating_order(a): # a must be sorted nondecreasingly
    j = len(a) - 1
    i = 0

    while i < j:
        yield a[j]
        yield a[i]
        j -= 1
        i += 1

    if i == j:
        yield a[i]

for _ in range(int(input())):
    print(*alternating_order(sorted(read_record())))
