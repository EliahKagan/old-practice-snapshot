#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    n, x, y = read_record()
    nx = ny = 0
    i = -1

    for j, e in enumerate(read_record()):
        if e == x:
            nx += 1
        if e == y:
            ny += 1
        if nx == ny:
            i = j

    print(i)
