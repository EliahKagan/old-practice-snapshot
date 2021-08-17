#!/usr/bin/env python3

def read_val():
    return int(input())

for _ in range(read_val()):
    n = read_val()
    k = read_val()
    print('Yes' if n & (1 << k) else 'No')
