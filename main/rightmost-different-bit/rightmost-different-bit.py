#!/usr/bin/env python3

def get_rightmost_set_position(bits):
    if bits == 0:
        return -1 # this special value indicates no bits are set

    pos = 1 # 1-based indexing
    while bits & 1 == 0:
        bits >>= 1
        pos += 1

    return pos

for _ in range(int(input())):
    m, n = map(int, input().split())
    print(get_rightmost_set_position(m ^ n))
