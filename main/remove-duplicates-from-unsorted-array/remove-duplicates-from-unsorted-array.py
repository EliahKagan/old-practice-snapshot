#!/usr/bin/env python3

def read_record():
    input() # don't need n
    return map(int, input().split())

def get_without_duplicates(values):
    s = set()
    for x in values:
        if x not in s:
            s.add(x)
            yield x

for _ in range(int(input())):
    print(*get_without_duplicates(read_record()))
