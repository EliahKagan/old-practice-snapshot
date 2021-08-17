#!/usr/bin/env python3

def enumerate_right(values):
    i = 0
    for x in values:
        yield (x, i)
        i += 1

def read_record():
    return map(int, input().split())

def read_indexed_record():
    return list(enumerate_right(read_record()))

for _ in range(int(input())):
    _, index = read_record() # don't need n
    values = read_indexed_record()
    key = values[index]
    values.sort()
    print(values.index(key))
