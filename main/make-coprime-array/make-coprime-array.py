#!/usr/bin/env python3

from math import gcd

for _ in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    print(sum(1 for i in range(0, len(a) - 1) if gcd(a[i], a[i + 1]) != 1))
