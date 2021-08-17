#!/usr/bin/env python3

import re

# To handle input (as in the example) that contains extraneous characters.
CHAR_REGEX = re.compile(r'\S')
INT_REGEX = re.compile(r'\d+')

def read_token(regex):
    return regex.search(input()).group()

def get_suffix(s, c, i, default = 'Empty string'):
    prefix = re.match(r'(?:[^%c]*%c){%d}' % (c, c, i), s)

    if prefix is None or prefix.end() == len(s):
        return default
    else:
        return s[prefix.end():]

for _ in range(int(input())):
    s = input().strip()
    c = read_token(CHAR_REGEX)
    i = int(read_token(INT_REGEX))
    print(get_suffix(s, c, i))
