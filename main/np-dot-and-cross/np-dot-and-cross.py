#!/usr/bin/env python3

import numpy

def read_square_matrix(size):
    matrix = numpy.array([input().split() for _ in range(size)], int)
    if matrix.shape != (size, size):
        raise ValueError('wrong shape')
    return matrix

n = int(input())
a = read_square_matrix(n)
b = read_square_matrix(n)

print(a.dot(b))
