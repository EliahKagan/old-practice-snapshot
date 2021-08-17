#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def special_sort(items):
    a = sorted(items)

    i = 0
    j = len(a) - 1

    while i < j:
        yield a[i]
        yield a[j]
        i += 1
        j -= 1

    if i == j:
        yield a[i]

for _ in range(int(input())):
    input() # don't need n
    print(*special_sort(read_record()))
