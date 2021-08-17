#!/usr/bin/env python3

def fib(bound):
    a = 0
    b = 1
    
    while a <= bound:
        yield a
        a, b = b, a + b

FIB = set(fib(1000))

for t in range(int(input())):
    input() # don't need n
    ans = (x for x in map(int, input().split()) if x in FIB)
    print(' '.join(map(str, ans)))
