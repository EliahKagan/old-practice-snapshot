#!/usr/bin/env python3

def have_track(a, b):
    low = min(a, b)
    high = max(a, b)
    delta = high - low
    
    return delta == 2 or (delta == 1 and low % 2 != 0)

for t in range(int(input())):
    print('YES' if have_track(*map(int, input().split())) else 'NO')
