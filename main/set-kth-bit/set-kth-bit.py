#!/usr/bin/env python3

for _ in range(int(input())):
    n, k = map(int, input().split())
    print(n | 1 << k)
