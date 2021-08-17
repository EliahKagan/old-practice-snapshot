#!/usr/bin/env python3

for _ in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    
    best = 0
    for i in range(0, len(a) - 1):
        for j in range(i + 1, len(a)):
            best = max(best, a[i] & a[j])
    
    print(best)
