#!/usr/bin/env python3

def read_record():
    input() # don't need n
    return map(int, input().split())

def count_even_odd(values):
    even_odd = [0, 0]

    for x in values:
        even_odd[x % 2] += 1

    return even_odd

for _ in range(int(input())):
    even, odd = count_even_odd(read_record())
    print(even * odd)
