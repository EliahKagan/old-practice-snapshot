#!/usr/bin/env python3

from collections import defaultdict

for _ in range(int(input())):
    n = int(input())
    a = map(int, input().split())
    d = defaultdict(lambda: -1, ((x, x) for x in a))
    print(*(d[x] for x in range(n)))
