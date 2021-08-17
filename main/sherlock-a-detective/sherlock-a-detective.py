#!/usr/bin/env python3

for t in range(int(input())):
    n = int(input())
    s = set(range(1, n + 1)).difference(map(int, input().split()))
    print(*sorted(s))
