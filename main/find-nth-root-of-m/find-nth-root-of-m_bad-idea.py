#!/usr/bin/env python3

from math import floor

def find_root(n, m):
    root = pow(m, 1 / n)
    ans = floor(root)
    return ans if ans == root else -1

for t in range(int(input())):
    print(find_root(*map(int, input().split())))
