#!/usr/bin/env python3

import numpy

n, _ = map(int, input().split()) # don't need m
a = numpy.array([input().split() for _ in range(n)], int)
print(a.transpose())
print(a.flatten())
