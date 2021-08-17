#!/usr/bin/env python3

import collections

size = int(input())

def ok(*indices):
    return all(0 <= idx < size for idx in indices)

ii, ij, fi, fj = map(int, input().split())

if not ok(ii, ij, fi, fj):
    raise ValueError('a user-provided index is out of range')

def neighbors(i, j):
    return filter(ok, (i - 2, j - 1),  # UL
                      (i - 2, j + 1),  # UR
                      (i,     j + 2),  # R
                      (i + 2, j + 1),  # LR
                      (i + 2, j - 1),  # LL
                      (i_,    j - 2))  # L



def make_contour_map(i, j):
    grid = [[None for _j in range(size)] for _i in range(size)]

    queue = collections.deque((i, j),)
    level = 0
    while queue:
        for _ in range(len(queue)):
            i, j = queue.popleft()
            if grid[i][j] is not None:
                continue
            grid[i][j] = level
            if i == fi and j == fj:
                # Just return here? Do we need the contour map at all?