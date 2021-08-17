#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def count_jumps(x, y, heights):
    d = x - y
    jumps = 0
    
    for target in heights:
        cur = x
        jumps += 1
        
        while cur < target:
            cur += d
            jumps += 1
    
    return jumps

for t in range(int(input())):
    x, y, _ = read_record() # don't need n
    heights = list(read_record())
    print(count_jumps(x, y, heights))
