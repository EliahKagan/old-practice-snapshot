#!/usr/bin/env python3

import itertools

# Values:   1,  3,  5,  7,  9, 11, 13, 15, 17, 19, 21, ...
# Indices:  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, ...
#
# Where index i represents x, and j represents y = x**2:
#
#  x = 2i + 1      i = (x - 1) / 2
#  y = 2j + 1      j = 2i(i + 1)  because:
#
#  j = (y - 1) / 2 = (x**2 - 1) / 2 = ((2i + 1)**2 - 1) / 2
#    = (4 i**2 + 4i + 1 - 1) / 2 = 4i(i + 1) / 2 = 2i(i + 1)
#
# Where index h represents w, and k represents z = w + 2x:
#
#  w = 2h + 1      z = w + 2x = 2h + 1 + 2(2i + 1) = 2(h + 2i + 1) + 1
#  z = 2k + 1      k = (z - 1) / 2 = h + 2i + 1 = h + x
def sieve(maxval):
    if maxval < 2:
        return itertools.chain() # empty
    
    size = (maxval + 1) // 2
    a = [True] * size
    a[0] = False # 1 is not prime
    
    for i in itertools.count(1): # from 3
        j = 2 * i * (i + 1)
        if j >= size:
            break
        
        for k in range(j, size, 2 * i + 1):
            a[k] = False
    
    odd_primes = (2 * i + 1 for i, e in enumerate(a) if e)
    return itertools.chain((2,), odd_primes)

print(*sieve(100))
