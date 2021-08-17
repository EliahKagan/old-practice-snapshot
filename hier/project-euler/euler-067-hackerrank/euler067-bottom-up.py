#!/usr/bin/env python3

def read_value():
    return int(input())

def read_record():
    return list(map(int, input().split()))

for _ in range(read_value()):
    grid = [read_record() for _ in range(read_value())]
    
    for i in range(1, len(grid)):
        # accumulate the only available "choices" into the two edge cells
        for j in 0, -1:
            grid[i][j] += grid[i - 1][j]
        
        # accumulate the best of two real choices into all non-edge cells
        for j in range(1, len(grid[i]) - 1):
            grid[i][j] += max(grid[i - 1][j - 1], grid[i - 1][j])
    
    print(max(grid[-1]))
