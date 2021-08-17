#!/usr/bin/env python3

from itertools import chain

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    input() # don't need n, m
    a = read_record()
    b = read_record()
    print(*sorted(chain(a, b)))
