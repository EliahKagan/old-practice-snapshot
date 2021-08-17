#!/usr/bin/env python3

for t in range(int(input())):
    n = int(input())
    d = [0] * (n + 1)
    
    for i in range(1, n + 1):
        for j in range(i, n + 1, i):
            d[j] ^= 1
    
    print(*d[1:])
