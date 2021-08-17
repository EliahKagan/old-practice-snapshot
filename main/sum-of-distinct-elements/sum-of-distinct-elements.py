#!/usr/bin/env python3

def read_record():
    input() # don't need n
    return map(int, input().split())

for _ in range(int(input())):
    print(sum(frozenset(read_record())))
