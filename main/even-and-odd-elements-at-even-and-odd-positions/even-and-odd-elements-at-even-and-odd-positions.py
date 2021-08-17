#!/usr/bin/env python3

def read_record():
    input() # don't need n
    return map(int, input().split())

def decompose_even_odd(values):
    even_odd = ([], [])

    for x in values:
        even_odd[x % 2].append(x)

    return even_odd

def recombine(evens, odds):
    istop = len(evens)
    jstop = len(odds)
    i = j = 0

    while i != istop and j != jstop:
        yield evens[i]
        yield odds[j]
        i += 1
        j += 1

    while i != istop:
        yield evens[i]
        i += 1

    while j != jstop:
        yield odds[j]
        j += 1

for _ in range(int(input())):
    print(*recombine(*decompose_even_odd(read_record())))
