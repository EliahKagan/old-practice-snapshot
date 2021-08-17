#!/usr/bin/env python3

PRECISION = 5
SUFFIX = '.' + '0' * PRECISION
SUFFIX_LEN = len(SUFFIX)


def prettify(x):
    s = '%.*f' % (PRECISION, x)
    return s[:-SUFFIX_LEN] if s.endswith(SUFFIX) else s

def pos_neg_zero_ratios(a):
    pos = neg = zer = 0
    
    for k in a:
        if k > 0:
            pos += 1
        elif k != 0:
            neg += 1
        else:
            zer += 1
    
    n = pos + neg + zer
    return n / pos, n / neg, n / zer

def read_record():
    input() # don't need n
    return map(int, input().split())

for _ in range(int(input())):
    for x in pos_neg_zero_ratios(read_record()):
        print(prettify(x))
