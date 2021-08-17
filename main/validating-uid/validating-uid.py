#!/usr/bin/env python3

from collections import Counter

LEN = 10
MIN_UPPERS = 2
MIN_DIGITS = 3

def count_if(items, predicate):
    return sum(1 for item in items if predicate(item))

def is_valid(uid):
    return (LEN == len(uid) == len(Counter(uid)) == count_if(uid, str.isalnum)
            and count_if(uid, str.isupper) >= MIN_UPPERS
            and count_if(uid, str.isdigit) >= MIN_DIGITS)

for _ in range(int(input())):
    print('Valid' if is_valid(input().strip()) else 'Invalid')
