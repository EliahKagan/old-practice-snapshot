#!/usr/bin/env python3

def josephus(n, k):
    'Solves the josephus problem using the naive algorithm.'
    assert n > 0 and k > 0
    k -= 1

    a = list(range(1, n + 1))
    i = 0

    while len(a) != 1:
        i = (i + k) % len(a)
        del a[i]

    return a[0]

for t in range(int(input())):
    print(josephus(int(input()), 2))
