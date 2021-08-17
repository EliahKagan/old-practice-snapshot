#!/usr/bin/env python3

def read_record():
    input() # don't need n
    return map(int, input().split())

def frequencies(items):
    it = iter(sorted(items))

    freq = 1
    prev = next(it)

    for cur in it:
        if cur == prev:
            freq += 1
        else:
            yield freq
            freq = 1
            prev = cur

    yield freq

for _ in range(int(input())):
    print(*frequencies(read_record()))
