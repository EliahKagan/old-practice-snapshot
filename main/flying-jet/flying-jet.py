#!/usr/bin/env python3

def speed(n):
    return 7 * 3**(n // 2 - 1) if n % 2 == 0 else (n // 2 + 1)**4

def get():
    return int(input())

for _ in range(get()):
    print(speed(get()))
