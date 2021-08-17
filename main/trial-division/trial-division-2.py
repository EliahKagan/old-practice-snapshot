#!/usr/bin/env python3

from itertools import takewhile
from math import sqrt

def trial_division(n):
    '''Returns a list of all primes up to n.'''
    a = [2]
    
    for i in range(3, n + 1, 2):
        s = int(sqrt(i))
        
        if all(i % j != 0 for j in takewhile(lambda k: k <= s, a)):
            a.append(i)
    
    return a

print(*trial_division(int(input())))
