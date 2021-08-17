#!/usr/bin/env python3

for _ in range(int(input())):
    n = int(input())
    print('NO' if '0' in bin(n)[2:] else 'YES')
