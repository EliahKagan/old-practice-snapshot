#!/usr/bin/env python3

import numpy

n, m = map(int, input().split())
a = numpy.array([input().split() for _ in range(n)], int)

if a.shape != (n, m):
    raise ValueError('wrong shape')

print(a.sum(0).prod())
