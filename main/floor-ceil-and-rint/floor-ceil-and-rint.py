#!/usr/bin/env python3

import numpy

a = numpy.array(input().split(), float)
print(numpy.floor(a), numpy.ceil(a), numpy.rint(a), sep='\n')
