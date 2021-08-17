#!/usr/bin/env python3

for _ in range(int(input())):
    a, b, m = map(int, input().split())

    left = a // m * m
    if left != a:
        a = left + m

    b = b // m * m

    print(0 if a > b else 1 + (b - a) // m)
