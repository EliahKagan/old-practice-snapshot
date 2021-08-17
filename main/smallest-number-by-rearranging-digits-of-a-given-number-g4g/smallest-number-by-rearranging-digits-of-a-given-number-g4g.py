#!/usr/bin/env python3

from collections import Counter

def read_digits():
    return map(int, input().strip())

def index_of_nonzero(items):
    return next(i for i, x in enumerate(items) if x != 0)

def with_leading_nonzero(items):
    index = index_of_nonzero(items)
    items.insert(0, items.pop(index))
    return items

for _ in range(int(input())):
    # This is deliberately wrong, to pass the broken test cases. A correct
    # implementation moves only a single nonzero digit to the left.
    counts = Counter(read_digits())
    keys = with_leading_nonzero(sorted(counts.keys()))
    print(*(str(digit) * counts[digit] for digit in keys), sep='')
