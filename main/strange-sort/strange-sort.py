#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def strange_sort(a, j):
    b = a[:j] + a[j + 1:]
    b.sort()
    b.insert(j, a[j])
    return b

for _ in range(int(input())):
    _, k = read_record()  # don't need n
    a = list(read_record())
    print(*strange_sort(a, k - 1))
