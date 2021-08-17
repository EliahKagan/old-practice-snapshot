#!/usr/bin/env python

from sys import stderr

MOD = 10**9 + 7 # maze paths will be reported (and computed) modulo this value

RIGHT_ONLY = 1
DOWN_ONLY = 2
RIGHT_OR_DOWN = 3

CHECK_RANGE = False
DEBUG_TABULATION = False # prints tables at the end, to standard error

def create_uniform_grid(size, element):
    return [[element] * size for _ in range(size)]

for _ in range(int(input())):
    # Read maze size and maze.
    n = int(input())
    if not 0 < n <= 1000:
        raise ValueError('wrong maze size')
    maze = [list(map(int, input().split())) for _ in range(n)]
    if any(len(row) != n for row in maze):
        raise ValueError('wrong maze shape')

    # Optionally, validate each element of the maze. Disable this for speed.
    if CHECK_RANGE and not all(all(RIGHT_ONLY <= elem <= RIGHT_OR_DOWN
                                   for elem in row) for row in maze):
        raise ValueError('bad value in grid')

    # Create matrices for all cells' reachability, path counts, and adventure.
    # Reachability information is needed because a path count can hit MOD and
    # wrap around, in which case it might wrongly indicate unreachability.
    reachable = create_uniform_grid(n, False)
    reachable[0][0] = True
    paths = create_uniform_grid(n, 0)
    paths[0][0] = 1
    adventure = create_uniform_grid(n, 0)
    adventure[0][0] = maze[0][0]

    # Compute "adventure" values and path counts for the top row.
    for j in range(1, n):
        if maze[0][j - 1] == DOWN_ONLY:
            break
        reachable[0][j] = True
        paths[0][j] = 1
        adventure[0][j] = maze[0][j] + adventure[0][j - 1]

    # Compute "adventure" values and path counts for the left column.
    for i in range(1, n):
        if maze[i - 1][0] == RIGHT_ONLY:
            break
        reachable[i][0] = True
        paths[i][0] = 1
        adventure[i][0] = maze[i][0] + adventure[i - 1][0]

    # Compute "adventure" values and path counts for the rest of the maze.
    for i in range(1, n):
        for j in range(1, n):
            from_above = reachable[i - 1][j] and maze[i - 1][j] != RIGHT_ONLY
            from_left = reachable[i][j - 1] and maze[i][j - 1] != DOWN_ONLY

            if not (from_above or from_left):
                continue

            reachable[i][j] = True

            if from_above:
                paths[i][j] += paths[i - 1][j]
                adventure[i][j] = max(adventure[i][j], adventure[i - 1][j])

            if from_left:
                paths[i][j] += paths[i][j - 1]
                adventure[i][j] = max(adventure[i][j], adventure[i][j - 1])

            paths[i][j] %= MOD
            adventure[i][j] += maze[i][j]

    print(paths[-1][-1], adventure[-1][-1])

    if DEBUG_TABULATION:
        print('REACHABLE:', reachable, '', 'PATHS:', paths, '',
              'ADVENTURE:', adventure, sep='\n', file=stderr)
