#!/usr/bin/env python3

def gcd(m, n):
    return m if n == 0 else gcd(n, m % n)

for _ in range(int(input())):
    print(gcd(*map(int, input().split())))
