#!/usr/bin/env python3

def read_record():
    input() # don't need n
    return map(int, input().split())

def frequencies(items):
    it = iter(sorted(items))
    prev = next(it)
    freq = 1

    for cur in it:
        if prev != cur:
            yield freq
            prev = cur
        freq += 1

    yield freq

for _ in range(int(input())):
    print(*frequencies(read_record()))
