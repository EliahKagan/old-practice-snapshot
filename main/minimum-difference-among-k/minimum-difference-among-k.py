#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    n, k = read_record()
    a = sorted(read_record())
    assert len(a) == n

    d = k - 1
    print(min(a[i + d] - a[i] for i in range(n - d)))
