#!/usr/bin/env python3

import numpy

def read_array(n, m):
    ret = numpy.array([input().split() for _ in range(n)], int)
    if ret.shape != (n, m):
        raise ValueError('wrong shape')
    return ret

n, m = map(int, input().split())
a = read_array(n, m)
b = read_array(n, m)

print(a + b, a - b, a * b, a // b, a % b, a**b, sep='\n')
