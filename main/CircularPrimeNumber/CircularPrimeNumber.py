#!/usr/bin/env python

from bisect import bisect_left
from itertools import chain, takewhile
from math import sqrt

class Primes():
    'computes, stores, and performs computations with a range of prime numbers'

    @staticmethod
    def _nsqrt(n):
        'integer square root via float (accurate for small integers)'
        return int(sqrt(n))

    @staticmethod
    def _rotations(n):
        'generates all the digit-rotations of n (including duplicates)'
        yield n

        s = str(n)
        for i in xrange(1, len(s)):
            yield int(s[i:] + s[:i])

    def __init__(self, n):
        'create an instance with enough primes to factor any number up to n'
        pmax = Primes._nsqrt(n)
        a = [True] * (pmax + 1)

        for i in xrange(3, Primes._nsqrt(pmax) + 1):
            if a[i]:
                for j in xrange(i * i, len(a), i * 2):
                    a[j] = False

        tail = (p for p in xrange(3, len(a), 2) if a[p])
        self._elems = list(chain((2,), tail))

        self._max_factorable = max(n, self._elems[-1]**2)

    def max_factorable(self):
        'gets the maximum value that this object can check for primality'
        return self._max_factorable

    def is_prime(self, n):
        'check if n is prime, where n <= self.max_factorable()'
        if n <= self._elems[-1]:
            return self._elems[bisect_left(self._elems, n)] == n

        if n <= self.max_factorable():
            s = Primes._nsqrt(n)

            for p in takewhile(lambda p_: p_ <= s, self._elems):
                if n % p == 0:
                    return False

            return True

        fmt = "can't check primality of %d, since %d > %d"
        raise ValueError(fmt % (n, n, self.max_factorable()))

    def is_circular_prime(self, n):
        return all(self.is_prime(k) for k in Primes._rotations(n))

def get():
    'read a line of input as an integer'
    return int(raw_input())

MAX_AFTER_ROTATION = 10000
primes = Primes(MAX_AFTER_ROTATION)

for k in (get() for i in xrange(get())):
    print int(primes.is_circular_prime(k))
