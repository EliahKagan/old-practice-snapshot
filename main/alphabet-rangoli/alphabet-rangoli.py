#!/usr/bin/env python3

from itertools import chain

def bounce(high, low):
    return chain(range(high, low, -1), range(low, high + 1))

def get_row_chars(high_ord, low_ord):
    return map(chr, bounce(high_ord, low_ord))

def get_row(high_ord, low_ord):
    return '-'.join(get_row_chars(high_ord, low_ord))

def print_line(width, high_ord, low_ord):
    print(get_row(high_ord, low_ord).center(width, '-'))

def print_rangoli(size):
    width = size * 4 - 3
    high_ord = ord('a') + size - 1
    
    for low_ord in bounce(high_ord, ord('a')):
        print_line(width, high_ord, low_ord)
