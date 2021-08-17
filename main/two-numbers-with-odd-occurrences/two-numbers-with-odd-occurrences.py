#!/usr/bin/env python3

MAX_HIGH_BIT = 2**31

def get_high_bit(n):
    assert n > 0
    
    b = MAX_HIGH_BIT
    while not (n & b):
        b >>= 1
    
    return b

def get_odd_occurring_pair_xor(a):
    acc = 0
    for x in a:
        acc ^= x
    
    assert acc != 0 # if it were, there would be no odd-occurring numbers
    return acc

def get_odd_occurring_pair(a):
    b = get_high_bit(get_odd_occurring_pair_xor(a))
    big = small = 0
    
    for x in a:
        if x & b:
            big ^=x
        else:
            small ^= x
    
    return big, small

def read_record():
    return list(map(int, input().split()))
    
for _ in range(int(input())):
    input() # don't need n
    print(*get_odd_occurring_pair(read_record()))
