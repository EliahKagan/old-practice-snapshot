#!/usr/bin/env python3

import numpy

n, m = map(int, input().split())
a = numpy.array([input().split() for _ in range(n)], float)

if a.shape != (n, m):
    raise ValueError('wrong shape')

print(a.mean(1), a.var(0), a.std(), sep='\n')
