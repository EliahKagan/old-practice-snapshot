#!/usr/bin/env python3

def trial_division(n):
    '''Returns a list of all primes up to n.'''
    a = [2]
    
    for i in range(3, n + 1, 2):
        if all(i % j != 0 for j in a):
            a.append(i)
    
    return a

print(*trial_division(int(input())))
