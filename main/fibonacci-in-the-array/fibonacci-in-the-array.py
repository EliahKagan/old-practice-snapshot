#!/usr/bin/env python3

def fibonacci(a, b, bound):
    yield a
    
    while b <= bound:
        yield b
        a, b = b, a + b

FIBONACCI = frozenset(fibonacci(0, 1, 10000))

for _ in range(int(input())):
    input() # don't need n
    print(sum(1 for tok in input().split() if int(tok) in FIBONACCI))
