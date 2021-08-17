#!/usr/bin/env python3
# This assumes a single component, other than isolated vertices.

def read_val():
    return int(input())

def read_record():
    return map(int, input().split())

for _ in range(read_val()):
    n = read_val()
    odds = sum(sum(read_record()) % 2 for _ in range(n))
    print(1 if odds in (0, 2) else 0)
