#!/usr/bin/env python3

n, m, k = map(int, input().split())
a = [[None] * n for _ in range(n)]

for i in range(n): # this approach is needlessly slow, but self-documenting
    for j in range(n):
        if i == 0 and j == 0:
            a[i][j] = m
        elif i == j:
            a[i][j] = a[i - 1][j - 1] + k
        elif i > j:
            a[i][j] = a[i - 1][j] - 1
        elif i < j:
            a[i][j] = a[i][j - 1] - 1
        else:
            raise AssertionError("numbers didn't compare!")

for row in a:
    print(*row)
