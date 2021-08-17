#!/usr/bin/env python3

MAX_VALUE = 1000

def read_record():
    input() # don't need n
    return map(int, input().split())

def count_pairs(xs):
    unpaired = [False] * (MAX_VALUE + 1)
    acc = 0
    
    for x in xs:
        if unpaired[x]:
            unpaired[x] = False
            acc += 1
        else:
            unpaired[x] = True
    
    return acc

for _ in range(int(input())):
    print(count_pairs(read_record()) * 2)
