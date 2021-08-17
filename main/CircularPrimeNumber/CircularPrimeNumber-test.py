from bisect import bisect_left
from itertools import chain, takewhile
from math import sqrt

def nsqrt(n):
    'integer square root by converting to/from float (accurate for small ints)'
    return int(sqrt(n))

class Primes():
    def __init__(self, n):
        'create an instance that stores primes up to n'
        self.__max = n

        a = [True] * (n + 1)
        
        for i in xrange(3, nsqrt(n) + 1):
            if a[i]:
                for j in xrange(i * i, len(a), i * 2):
                    a[j] = False

        tail = (k for k in xrange(3, len(a), 2) if a[k])
        self.__elems = list(chain((2,), tail))

    def max(self):
        'gets the maximum value that this object can check for primality'
        return self.__max

    def is_prime(self, n):
        'check if n is prime, where n <= self.max()'
        if n <= self.__elems[-1]:
            return self.__elems[bisect_left(self.__elems, n)] == n

        if n <= self.max():
            s = nsqrt(n)

            for p in takewhile(lambda p_: p_ <= s, self.__elems):
                if n % p == 0:
                    return False

            return True

        fmt = "can't check primality of %d, since %d > %d"
        raise ValueError(fmt % (n, n, self.max()))

n = 10000
primes = Primes(n)

for p in filter(primes.is_prime, xrange(1, n + 1)):
    print p
