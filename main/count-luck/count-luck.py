#!/usr/bin/env python3

import contextlib


def read_value():
    """Reads a line as a single integer."""
    return int(input())


def read_record():
    """Reads a line as a record of integers."""
    return map(int, input().split())


def read_row(width):
    """Reads a grid row of the specific width."""
    row = list(input().strip())
    if len(row) != width:
        raise ValueError('wrong row width')
    return row


def read_grid():
    """Reads a height value, width value, and rows as a grid."""
    height, width = read_record()
    return [read_row(width) for _ in range(height)]


def height(grid):
    """Gets the height of a rectangular grid (stored row-major)."""
    return len(grid)


def width(grid):
    """Gets the width of a rectangular grid (stored row-major)."""
    try:
        return len(grid[0])
    except IndexError:
        return 0


def find_start(grid):
    """Finds the coordinates of the start mark "M" in the grid."""
    for i, row in enumerate(grid):
        with contextlib.suppress(ValueError):
            return (i, row.index('M'))

    raise ValueError('start mark "M" not found in grid')


def can_go(grid, i, j):
    """Checks if the cell (i, j) is on the grid and accessible."""
    return 0 <= i < height(grid) and 0 <= j < width(grid) and grid[i][j] != 'X'


"""count_junctions returns this when its caller needs to backtrack."""
GOT_STUCK = -1


def count_junctions(grid, i, j):
    """
    Counts the number of junctions from (i, j) to the finish ("*").
    Mutates grid, filling at least some of it in with "X"es.
    """
    if grid[i][j] == 'X':
        return GOT_STUCK

    if grid[i][j] == '*':
        return 0

    grid[i][j] = 'X'

    possible_neighbors = ((i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1))
    neighbors = [(h, k) for h, k in possible_neighbors if can_go(grid, h, k)]

    for h, k in neighbors:
        junctions = count_junctions(grid, h, k)
        if junctions != GOT_STUCK:
            return (1 if len(neighbors) > 1 else 0) + junctions

    return GOT_STUCK


def run():
    """
    Reads a grid and guess, counts junctions from start to finish,
    and reports if the guess was correct.
    """
    grid = read_grid()
    guess = read_value()

    junctions = count_junctions(grid, *find_start(grid))
    if junctions == GOT_STUCK:
        raise ValueError('could not find a path from start to finish')

    print('Impressed' if guess == junctions else 'Oops!')


if __name__ == '__main__':
    for _ in range(read_value()):
        run()
