#!/usr/bin/env python3

def read_inverse_permutation():
    input() # don't need n
    a = [int(tok) - 1 for tok in input().split()]
    
    b = [None] * len(a)
    for i in range(len(a)):
        b[a[i]] = i
    
    return b;

def total_distance(b):
    acc = 0
    
    for i in range(1, len(b)):
        acc += abs(b[i] - b[i - 1])
    
    return acc

for t in range(int(input())):
    print(total_distance(read_inverse_permutation()))
