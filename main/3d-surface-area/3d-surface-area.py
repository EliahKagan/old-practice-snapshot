#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def read_row():
    return (0, *read_record(), 0)

height, width = read_record()
nrows = height + 2
ncols = width + 2
zero_row = (0,) * ncols
board = (zero_row, *(read_row() for _ in range(height)), zero_row)

area = height * width * 2 # top and bottom

for i in range(nrows - 1):
    for j in range(ncols - 1):
        area += (abs(board[i][j] - board[i][j + 1])
               + abs(board[i][j] - board[i + 1][j]))

print(area)
