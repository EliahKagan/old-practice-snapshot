#!/usr/bin/env python3

for t in range(int(input())):
    input() # don't need n
    
    acc = 0
    for _ in range(2): # two lines of input
        for x in map(int, input().split()):
            acc ^= x
    
    print(acc)
