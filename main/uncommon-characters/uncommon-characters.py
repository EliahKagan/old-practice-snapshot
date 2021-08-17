#!/usr/bin/env python3

def read_chars():
    return frozenset(input().strip())

for _ in range(int(input())):
    print(''.join(sorted(read_chars() ^ read_chars())))
