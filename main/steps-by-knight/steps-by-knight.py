#!/usr/bin/env python3

import collections
import itertools

# Strangely, the code checker seems to require this when there's no solution.
UNREACHABLE = 1

# A knight (in ordinary chess) is a knight(A, B) = knight(1, 2)
A = 1
B = 2

def min_steps(n, i, j, ti, tj):
    if i == ti and j == tj:
        return 0

    vis = [[False for j in range(n)] for i in range(n)]
    vis[i][j] = True

    queue = collections.deque()
    queue.append((i, j))

    for depth in itertools.count(1):
        if not queue:
            return UNREACHABLE

        for _ in range(len(queue)):
            i, j = queue.popleft()

            for h, k in ((i - A, j - B), (i - A, j + B),
                         (i + A, j - B), (i + A, j + B),
                         (i - B, j - A), (i - B, j + A),
                         (i + B, j - A), (i + B, j + A)):
                if not (0 <= h < n and 0 <= k < n) or vis[h][k]:
                    continue

                vis[h][k] = True

                if h == ti and k == tj:
                    return depth

                queue.append((h, k))

def read_value():
    return int(input())

def read_record():
    return map(int, input().split())

for _ in range(read_value()):
    n = read_value()
    x, y = read_record()
    tx, ty = read_record()
    print(min_steps(n, x - 1, y - 1, tx - 1, ty - 1))
