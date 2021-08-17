#!/usr/bin/env python3

def read_state():
    return int(input()) // 2

last = read_state()
cur = read_state()

print(min(cur, last - cur))
