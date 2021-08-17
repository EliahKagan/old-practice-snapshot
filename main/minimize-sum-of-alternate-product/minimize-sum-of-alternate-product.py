#!/usr/bin/env python3

def sum_extreme_products(a): # assumes a is sorted
    acc = 0
    
    i = 0
    j = len(a) - 1
    while i < j:
        acc += a[i] * a [j]
        i += 1
        j -= 1
    
    return acc

for t in range(int(input())):
    input() # don't need n
    print(sum_extreme_products(sorted(map(int, input().split()))))
