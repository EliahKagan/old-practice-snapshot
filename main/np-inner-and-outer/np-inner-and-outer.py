#!/usr/bin/env python3

import numpy

def read_array():
    return numpy.array(input().split(), int)

a = read_array()
b = read_array()

print(numpy.inner(a, b))
print(numpy.outer(a, b))
