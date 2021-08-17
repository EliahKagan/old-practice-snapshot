#!/usr/bin/env python3

import collections
import itertools

UNROTTABLE = -1

EMPTY = 0
FRESH = 1
ROTTEN = 2

def time_to_rot(r, c, grid):
    fresh_count = 0
    queue = collections.deque()

    for i, j in itertools.product(range(r), range(c)):
        if grid[i][j] == FRESH:
            fresh_count += 1
        elif grid[i][j] == ROTTEN:
            queue.append((i, j))

    time = 0
    while fresh_count and queue:
        time += 1
        for _ in range(len(queue)):
            i, j = queue.popleft()

            for h, k in (i, j - 1), (i, j + 1), (i - 1, j), (i + 1, j):
                if 0 <= h < r and 0 <= k < c and grid[h][k] == FRESH:
                    grid[h][k] = ROTTEN
                    fresh_count -= 1
                    queue.append((h, k))

    return UNROTTABLE if fresh_count else time

def read_record():
    return map(int, input().split())

def as_grid(r, c, xs):
    xs = list(xs)
    if len(xs) != r * c:
        raise ValueError('wrong record length')

    it = iter(xs)
    return [list(itertools.islice(it, c)) for _ in range(r)]

for _ in range(int(input())):
    r, c = read_record()
    xs = read_record()
    grid = as_grid(r, c, xs)
    print(time_to_rot(r, c, grid))
