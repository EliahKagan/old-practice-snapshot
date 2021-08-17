#!/usr/bin/env python3

from bisect import bisect_left, bisect_right

for t in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    x = int(input())
    
    i = bisect_left(a, x)
    if i != len(a) and a[i] == x:
        print(i, bisect_right(a, x) - 1)
    else:
        print('-1')
