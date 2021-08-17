#!/usr/bin/env python3

s = set()
t = set()

for _ in range(int(input())):
    x, y = map(int, input().split())
    s.add(x)
    t.add(y)

print('YES' if len(s) == 1 or len(t) == 1 else 'NO')
