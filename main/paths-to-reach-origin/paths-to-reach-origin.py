#!/usr/bin/env python3

from math import factorial

def compute_path_count(n, m):
    return factorial(n + m) // factorial(n) // factorial(m)

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    print(compute_path_count(*read_record()))
