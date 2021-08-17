#!/usr/bin/env python3

def in_bounds(path, n, m):
    imin = imax = jmin = jmax = i = j = 0
    
    for move in path:
        if move == 'L':
            j -= 1
            jmin = min(jmin, j)
        elif move == 'R':
            j += 1
            jmax = max(jmax, j)
        elif move == 'U':
            i -= 1
            imin = min(imin, i)
        elif move == 'D':
            i += 1
            imax = max(imax, i)
        else:
            raise ValueError('can only move L, R, U, D')
    
    return imax - imin < n and jmax - jmin < m

for t in range(int(input())):
    i, j = map(int, input().split())
    print('1' if in_bounds(input().strip(), i, j) else '0')
