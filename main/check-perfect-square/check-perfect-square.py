#!/usr/bin/env python3

from math import sqrt

for _ in range(int(input())):
    n = int(input())
    r = int(sqrt(n))
    print('1' if r * r == n else '0')
