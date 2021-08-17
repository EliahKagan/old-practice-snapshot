#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    n, k = read_record()
    missing = set(range(1, n + k + 1))
    missing.difference_update(read_record())
    print(*sorted(missing)[:k])
