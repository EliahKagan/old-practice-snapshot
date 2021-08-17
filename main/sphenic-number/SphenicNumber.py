#!/usr/bin/env python

from itertools import chain
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

    def _is_possibly_sphenic(self, n):
        'helper method to check if n could plausibly be sphenic'
        if n > self.max_factorable():
            fmt = "can't check sphenicity of %d, since %d > %d"
            raise ValueError(fmt % (n, n, self.max_factorable()))

        return n >= 30

    def is_sphenic(self, n):
        'check if n is a sphenic number (3 prime divisors, all distinct)'
        if not self._is_possibly_sphenic(n):
            return False

        divisors_needed = 3

        for p in self._elems:
            if p * p > n:
                break

            if n % p != 0:
                continue

            n /= p
            if divisors_needed == 0 or n % p == 0:
                return False

            divisors_needed -= 1

        if n != 1:
            # we've removed all prime divisors from n less than its square
            # root, so what remains must be a single (large) prime divisor
            divisors_needed -= 1

        return divisors_needed == 0

def get():
    'read a line of input as an integer'
    return int(raw_input())

MAX_INPUT = 1000
primes = Primes(MAX_INPUT)

for k in (get() for i in xrange(get())):
    print int(primes.is_sphenic(k))
