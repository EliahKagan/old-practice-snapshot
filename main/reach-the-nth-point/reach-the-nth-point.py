#!/usr/bin/env python3

def ifib():
    a = 0
    b = 1
    while True:
        yield a
        a, b = b, a + b

fib_iter = ifib()
fibonacci = []

def fib(k):
    while len(fibonacci) <= k:
        fibonacci.append(next(fib_iter))

    return fibonacci[k]

def getval():
    return int(input())

for _ in range(getval()):
    print(fib(getval() + 1))
