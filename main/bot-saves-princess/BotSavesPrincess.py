#!/usr/bin/env python

from itertools import product

n = int(raw_input())
a = [raw_input().strip() for i in xrange(n)]
mi = mj = pi = pj = NOT_FOUND = -1

for i, j in product(xrange(n), xrange(n)):
    if a[i][j] == '-':
        continue

    if a[i][j] == 'm':
        assert mi == mj == NOT_FOUND
        mi = i
        mj = j
    elif a[i][j] == 'p':
        assert pi == pj == NOT_FOUND
        pi = i
        pj = j
    else:
        raise ValueError("invalid cell contents of '%c' encountered" % a[i][j])

assert mi != NOT_FOUND != mj and pi != NOT_FOUND != pj

for k in xrange(pi - mi):
    print 'DOWN'

for k in xrange(mi - pi):
    print 'UP'

for k in xrange(pj - mj):
    print 'RIGHT'

for k in xrange(mj - pj):
    print 'LEFT'
