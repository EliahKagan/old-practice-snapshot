#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    n, k = read_record()
    a = list(read_record())

    assert len(a) == n
    k %= n

    print(*a[k:], *a[:k])
