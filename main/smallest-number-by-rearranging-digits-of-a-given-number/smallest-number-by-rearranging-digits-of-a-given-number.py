#!/usr/bin/env python3

def read_digits():
    return map(int, input().strip())

def index_of_nonzero(items):
    return next(i for i, x in enumerate(items) if x != 0)

for _ in range(int(input())):
    digits = sorted(read_digits())
    index = index_of_nonzero(digits)
    digits.insert(0, digits.pop(index))
    print(*digits, sep='')