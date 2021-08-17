#!/usr/bin/env python3

from math import gcd

for _ in range(int(input())):
    print(gcd(*map(int, input().split())))
