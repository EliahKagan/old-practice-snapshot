#!/usr/bin/env python3

import numpy

def read_array(nrows):
    return numpy.array([input().split() for _ in range(nrows)], int)

n, m, _ = map(int, input().split()) # don't need p
a = read_array(n)
b = read_array(m)

print(numpy.concatenate([a, b]))
