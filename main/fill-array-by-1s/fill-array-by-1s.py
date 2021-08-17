#!/usr/bin/env python3

def first_not_of(a, key):
    '''An index to the first element of a not equal to key.'''
    i = 0
    for x in a:
        if x != key:
            return i
        i += 1

    return None

def last_not_of(a, key):
    '''An index to the last element of a not equal to key.'''
    i = len(a)
    while i != 0:
        i -= 1
        if a[i] != key:
            return i

    return None


def strip(a, key):
    '''A tuple (stripped, left, right) where left is the first index of an item
    besides key in a, right is one greater than the last index of key in a, and
    stripped is a[left:right].'''
    left = first_not_of(a, key)

    if left is None:
        return [], None, None

    right = last_not_of(a, key) + 1
    return (a[left:right], left, right)

def max_run_length(values, key):
    '''The maximum length of runs of key in an iterable, values.'''
    best = cur = 0

    for x in values:
        if x == key:
            cur += 1
        else:
            best = max(best, cur)
            cur = 0

    return max(best, cur)

def inner_fill_time(values, key):
    '''The number of steps it takes to fill an array of zeros with nonzero
    values, where in each step all adjacent positions of nonzeros, as well as
    the first and last positions, become nonzero. [Helper for fill_time().]'''
    return (max_run_length(values, key) + 1) // 2

def fill_time(a):
    '''The number of steps it takes to fill an array of zeros with nonzero
    values, where in each step all adjacent positions of nonzeros become
    nonzero, or -1 if this is impossible because all values in a are zero.'''
    key = 0
    b, i, j = strip(a, key)
    return -1 if i is None else max(i, len(a) - j, inner_fill_time(b, key))

for _ in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    print(fill_time(a))
