#!/usr/bin/env python3

from math import sqrt

def trial_division(n):
    '''Returns a list of all primes up to n.'''
    a = [2]
    
    def prime(i):
        '''Checks if i is indivisible by all the primes in a.'''
        s = int(sqrt(i))
        
        for j in a:
            if j > s:
                break
            if i % j == 0:
                return False
        
        return True
                
    
    for i in range(3, n + 1, 2):
        if prime(i):
            a.append(i)
    
    return a

print(*trial_division(int(input())))
