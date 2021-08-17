#!/usr/bin/env python3

from functools import reduce
from operator import mul

GRID_SIZE = 20  # the measure of each size of the grid
LENGTH = 4      # strand length

grid = [list(map(int, input().split())) for _ in range(GRID_SIZE)]
if any(len(row) != GRID_SIZE for row in grid):
    raise ValueError('wrong row length')

def products():
    for i in range(GRID_SIZE):
        for j in range(GRID_SIZE - LENGTH + 1):
            yield reduce(mul, (grid[i][j + d] for d in range(LENGTH)))

    for i in range(GRID_SIZE - LENGTH + 1):
        for j in range(GRID_SIZE):
            yield reduce(mul, (grid[i + d][j] for d in range(LENGTH)))

    for i in range(GRID_SIZE - LENGTH + 1):
        for j in range(GRID_SIZE - LENGTH + 1):
            yield reduce(mul, (grid[i + d][j + d] for d in range(LENGTH)))

    for i in range(GRID_SIZE - LENGTH + 1):
        for j in range(LENGTH - 1, GRID_SIZE):
            yield reduce(mul, (grid[i + d][j - d] for d in range(LENGTH)))

print(max(products()))
