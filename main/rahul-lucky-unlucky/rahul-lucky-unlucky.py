#!/usr/bin/env python3

from collections import deque

def read_coins():
    c = deque(map(lambda s: s == 'T', input().split()))
    c.appendleft(False) # so printed indices will look 1-based
    c.append(False) # so we can reach past the "end"; this can be anything
    return c

for t in range(int(input())):
    input() # don't need n
    c = read_coins()
    ops = []
    
    for i in range(1, len(c) - 1):
        if c[i]:
            c[i] = False
            c[i + 1] ^= True # boolean flip
            ops.append(i)
    
    print(len(ops))
    print(*ops)
