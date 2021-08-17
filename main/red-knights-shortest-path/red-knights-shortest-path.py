#!/usr/bin/env python3

import collections
import sys

def neighbors(i, j):
    return filter(ok, ((i - 2, j - 1),   # UL
                       (i - 2, j + 1),   # UR
                       (i,     j + 2),   # R
                       (i + 2, j + 1),   # LR
                       (i + 2, j - 1),   # LL
                       (i,     j - 2)))  # L

size = int(input())

start_i, start_j, end_i, end_j = map(int, input().split())

def ok(coords):
    i, j = coords
    return 0 <= i < size and 0 <= j < size

if not (ok((start_i, start_j)) and ok((end_i, end_j))):
    raise ValueError('a user-provided index is out of range')

if start_i == end_i and start_j == end_j:
    raise ValueError('start and end positions must be different')

grid = [[None for _j in range(size)] for _i in range(size)]
grid[start_i][start_j] = ()

queue = collections.deque()
queue.append((start_i, start_j))
dest_i = dest_j = None

while queue:
    src_i, src_j = queue.popleft()

    for dest_i, dest_j in neighbors(src_i, src_j):
        # Skip this cell if we have been here before.
        if grid[dest_i][dest_j] is not None:
            continue

        # Record how we got here.
        grid[dest_i][dest_j] = (src_i, src_j)

        # If this is the final destination, we're done.
        if dest_i == end_i and dest_j == end_j:
            queue.clear()
            break

        # Otherwise, we may later need to take another step from here.
        queue.append((dest_i, dest_j))

if grid[end_i][end_j] is None:
    # All possible paths are exhausted, and none reach the target cell.
    assert dest_i != end_i or dest_j != end_j
    print('Impossible')
    sys.exit(0)

assert dest_i == end_i and dest_j == end_j

while grid[dest_i][dest_j] != ():
    src_i, src_j = grid[dest_i][dest_j]
    assert src_j != dest_j, "directly connected cells shouldn't share a column"

    if dest_i < src_i:
        queue.appendleft('UL' if dest_j < src_j else 'UR')
    elif dest_i == src_i:
        queue.appendleft('L' if dest_j < src_j else 'R')
    else:
        queue.appendleft('LL' if dest_j < src_j else 'LR')

    dest_i = src_i
    dest_j = src_j

print(len(queue))
print(*queue)
