#!/usr/bin/env python3

def fib(n):
    a = 0
    b = 1
    for _ in range(n):
        yield b
        a, b = b, a + b

def getval():
    return int(input())

for _ in range(getval()):
    print(*fib(getval()))
