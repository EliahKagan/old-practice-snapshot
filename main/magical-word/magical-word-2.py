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

def compute_alpha_primes():
    '''Returns a sorted list of prime ordinal values of ASCII letters.'''
    ascii_size = 128
    ascii_primes = trial_division(ascii_size)

    ucase_left = bisect_left(ascii_primes, ord('A'))
    ucase_right = bisect_right(ascii_primes, ord('Z'))
    ucase_primes = ascii_primes[ucase_left:ucase_right]

    lcase_left = bisect_left(ascii_primes, ord('a'))
    lcase_right = bisect_right(ascii_primes, ord('z'))
    lcase_primes = ascii_primes[lcase_left:lcase_right]

    return ucase_primes + lcase_primes

ALPHA_PRIMES = compute_alpha_primes()
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
