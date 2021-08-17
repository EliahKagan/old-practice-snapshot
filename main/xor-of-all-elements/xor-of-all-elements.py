#!/usr/bin/env python3

def get_b(a):
    acc = 0;
    for x in a:
        acc ^= x
    
    b = [acc] * len(a)
    for i in range(len(a)):
        b[i] ^= a[i]
    
    return b

for t in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    print(*get_b(a))
