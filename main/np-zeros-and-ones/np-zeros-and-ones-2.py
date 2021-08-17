#!/usr/bin/env python3

import numpy

shape = list(map(int, input().split()))

for maker in numpy.zeros, numpy.ones:
    print(maker(shape, int))
