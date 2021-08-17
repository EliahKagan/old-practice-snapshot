#!/usr/bin/env python

from itertools import product

def get_pair():
    return map(int, raw_input().split())

bi, bj = get_pair() # bot coordinates
m = n = 5
a = [raw_input().strip() for i in xrange(m)]
assert all(len(row) == n for row in a)

min_distance = m + n
di = dj = None      # dirt coordinates

for i, j in product(xrange(m), xrange(n)):
    if a[i][j] == 'd':
        distance = abs(i - bi) + abs(j - bj)

        if distance < min_distance:
            min_distance = distance
            di = i
            dj = j

if di is None or dj is None:
    raise ValueError('no dirty cells found')

if bj < dj:
    print 'RIGHT'
elif bj > dj:
    print 'LEFT'
elif bi < di:
    print 'DOWN'
elif bi > di:
    print 'UP'
else:
    print 'CLEAN'
