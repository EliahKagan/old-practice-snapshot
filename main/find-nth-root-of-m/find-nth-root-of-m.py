#!/usr/bin/env python3

def find_root(n, m):
    r = int(pow(m, 1 / n))
    
    if r**n == m:
        return r
    
    if (r + 1)**n == m:
        return r + 1
    
    return -1

for t in range(int(input())):
    print(find_root(*map(int, input().split())))
