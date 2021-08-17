#!/usr/bin/env python3

from bisect import bisect_left, bisect_right
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

ASCII_SIZE = 128
ASCII_PRIMES = trial_division(ASCII_SIZE)

UCASE_LEFT = bisect_left(ASCII_PRIMES, ord('A'))
UCASE_RIGHT = bisect_right(ASCII_PRIMES, ord('Z'))
UCASE_PRIMES = ASCII_PRIMES[UCASE_LEFT:UCASE_RIGHT]

LCASE_LEFT = bisect_left(ASCII_PRIMES, ord('a'))
LCASE_RIGHT = bisect_right(ASCII_PRIMES, ord('z'))
LCASE_PRIMES = ASCII_PRIMES[LCASE_LEFT:LCASE_RIGHT]

ALPHA_PRIMES = UCASE_PRIMES + LCASE_PRIMES
ALPHA_PRIMES_LEN = len(ALPHA_PRIMES)

def get_nearest_alpha_prime(n):
    '''Gives the closest PRIMES value to n (if there is a tie, the smaller).'''
    i = bisect_left(ALPHA_PRIMES, n)

    if i == 0: # just return smallest value
        return ALPHA_PRIMES[0]

    if i == ALPHA_PRIMES_LEN: # just return biggest value
        return ALPHA_PRIMES[-1]

    left = ALPHA_PRIMES[i - 1]
    right = ALPHA_PRIMES[i]
    return right if right - n < n - left else left

def get_nearest_alpha_prime_char(c):
    return chr(get_nearest_alpha_prime(ord(c)))

def map_to_nearest_alpha_prime_chars(s):
    return ''.join(map(get_nearest_alpha_prime_char, s))

def get_magical_word(s):
    return map_to_nearest_alpha_prime_chars(s.strip())

for _ in range(int(input())):
    input() # don't need n
    print(get_magical_word(input()))
