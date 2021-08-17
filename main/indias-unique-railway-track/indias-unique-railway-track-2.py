#!/usr/bin/env python3

def have_track(a, b):
    delta = abs(a - b)
    return delta == 2 or (delta == 1 and min(a, b) % 2 != 0)

for t in range(int(input())):
    print('YES' if have_track(*map(int, input().split())) else 'NO')
