#!/usr/bin/env python3

def get_record():
    return map(int, input().split())

def idiv_round_up(numerator, denominator):
    '''Divides two positive integers and rounds up.'''
    return (numerator + denominator - 1) // denominator

MOD = 10**9 + 7

def make_monotone_decreasing(a, k):
    '''Makes the list a monotone decreasing (i.e., nonincreasing) by
    subtracting the positive value k zero or more times from each elements.
    Returns the total number of times k was subtracted.'''
    tot = 0

    for i in range(1, len(a)):
        rise = max(a[i] - a[i - 1], 0)
        cur = idiv_round_up(rise, k)
        a[i] -= k * cur
        tot = (tot + cur) % MOD

    return tot

for _ in range(int(input())):
    _, k = get_record() # don't need n
    a = list(get_record())
    print(make_monotone_decreasing(a, k))
