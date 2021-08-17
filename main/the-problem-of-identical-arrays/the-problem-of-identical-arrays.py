#!/usr/bin/env python3

def read_and_sort():
    return sorted(map(int, input().split()))

for _ in range(int(input())):
    input() # don't need n
    print(1 if read_and_sort() == read_and_sort() else 0)
