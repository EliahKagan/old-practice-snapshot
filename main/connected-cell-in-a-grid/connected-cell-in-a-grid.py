#!/usr/bin/env python3


def read_value():
    """Reads a single line as an integer."""
    return int(input())


def read_row(width):
    """Reads one row of integers interpreted as booleans."""
    row = [int(field) != 0 for field in input().split()]
    if len(row) != width:
        raise ValueError('wrong row width')
    return row


def read_grid():
    """Reads a grid of integers interpreted as booleans."""
    height = read_value()
    width = read_value()
    return [read_row(width) for _ in range(height)]


def height(grid):
    """Gets the height of the grid (stored in row-major order)."""
    return len(grid)


def width(grid):
    """Gets the width of the grid (stored in row-major order)."""
    try:
        return len(grid[0])
    except IndexError:
        return 0


def can_go(grid, i, j):
    """Checks if (i, j) is on the grid and accessible."""
    return 0 <= i < height(grid) and 0 <= j < width(grid) and grid[i][j]


def fill(grid, i, j):
    """Fills the (i, j) region of nonzeros in grid and returns its area."""
    if not can_go(grid, i, j):
        return 0

    grid[i][j] = False
    return 1 + sum(fill(grid, h, k) for h in range(i - 1, i + 2)
                                    for k in range(j - 1, j + 2))

def run():
    """Reports the biggest component in a grid read from standard input."""
    grid = read_grid()

    print(max(fill(grid, i, j) for i in range(height(grid))
                               for j in range(width(grid))))

if __name__ == '__main__':
    run()
