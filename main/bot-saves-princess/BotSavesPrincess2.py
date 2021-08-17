#!/usr/bin/env python

from itertools import product

n = int(raw_input())

got_m = False
mi, mj = map(int, raw_input().split())
pi = pj = NOT_FOUND = -1

a = [raw_input().strip() for i in xrange(n)]

for i, j in product(xrange(n), xrange(n)):
    if a[i][j] == '-':
        continue

    if a[i][j] == 'm':
        assert mi == i and mj == j
        got_m = True
    elif a[i][j] == 'p':
        assert pi == pj == NOT_FOUND
        pi = i
        pj = j
    else:
        raise ValueError("invalid cell contents of '%c' encountered" % a[i][j])

assert got_m and pi != NOT_FOUND != pj

if mi < pi:
    print 'DOWN'
elif mi > pi:
    print 'UP'
elif mj < pj:
    print 'RIGHT'
elif mj > pj:
    print 'LEFT'
else:
    raise ValueError('bot and princess coincide at (%d, %d), this is a bug'
                     % (mi, mj))
