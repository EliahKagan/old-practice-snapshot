#!/usr/bin/env python3

def is_maxheap(a, i=0):
    j = i * 2 + 1
    if j < len(a):
        if a[i] < a[j] or not is_maxheap(a, j):
            return False
        
        k = j + 1
        if k < len(a) and (a[i] < a[k] or not is_maxheap(a, k)):
            return False
    
    return True

for t in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    print('1' if is_maxheap(a) else '0')
