#!/usr/bin/env python3

import numpy

n = int(input())
a = numpy.array([input().split() for _ in range(n)], float)

if a.shape != (n, n):
    raise ValueError('wrong shape')

print(numpy.linalg.det(a))
