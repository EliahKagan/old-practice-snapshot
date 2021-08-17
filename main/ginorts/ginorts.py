#!/usr/bin/env python3

# order classes
LOWER = 0
UPPER = 1
ODD = 2
EVEN = 3

def get_order_class(ch):
    if ch.islower():
        return LOWER
    if ch.isupper():
        return UPPER
    if int(ch) % 2 != 0:
        return ODD
    return EVEN

chars = sorted(input().strip(), key=lambda ch: (get_order_class(ch), ch))
print(*chars, sep='')
