#!/usr/bin/env python3

def read_digits():
    return map(int, input().strip())

def index_of_nonzero(items):
    return next(i for i, x in enumerate(items) if x != 0)

def with_leading_nonzero(items):
    index = index_of_nonzero(items)
    items.insert(0, items.pop(index))
    return items

for _ in range(int(input())):
    digits = sorted(read_digits())
    print(*with_leading_nonzero(digits), sep='')
