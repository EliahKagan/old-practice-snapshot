#!/usr/bin/env python3

def round_down_to_even(value):
    return value & ~1

for _ in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))

    for i in range(0, round_down_to_even(len(a)), 2):
        if a[i] > a[i + 1]:
            a[i], a[i + 1] = a[i + 1], a[i]

    print(*a)
