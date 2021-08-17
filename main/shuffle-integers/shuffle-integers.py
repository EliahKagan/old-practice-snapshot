#!/usr/bin/env python3

def get_record():
    input() # don't need n
    return list(map(int, input().split()))

def insert(a, i, j):
    e = a[j]

    while i < j:
        a[j] = a[j - 1]
        j -= 1

    a[i] = e

def shuffle(a):
    half = len(a) // 2
    full = half * 2 # because len(a) might be odd

    i = 1
    for j in range(half, full):
        insert(a, i, j)
        i += 2

for _ in range(int(input())):
    a = get_record()
    shuffle(a)
    print(*a)
