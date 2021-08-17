#!/usr/bin/env python3

def fib(n):
    a = 0
    b = 1
    while a <= n:
        yield a
        a, b = b, a + b

def get():
    return int(input())

for _ in range(get()):
    print(*fib(get()))
