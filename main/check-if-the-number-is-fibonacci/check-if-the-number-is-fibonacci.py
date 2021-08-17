#!/usr/bin/env python3

def fib(bound):
    a = 0
    b = 1
    
    while a <= bound:
        yield a
        a, b = b, a + b

FIB = set(fib(100))

for t in range(int(input())):
    print('Yes' if int(input()) in FIB else 'No')
