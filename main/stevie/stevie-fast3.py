#!/usr/bin/python3

from collections import defaultdict

def read_record():
    return list(map(int, input().split()))

def get_aval_to_max_bval_map(a, b):
    aval_to_max_bval = defaultdict(int)

    for x, y in zip(a, b):
        if aval_to_max_bval[x] < y:
            aval_to_max_bval[x] = y

    return aval_to_max_bval

_ = input() # don't need n
a = read_record()
b = read_record()

aval_to_max_bval = get_aval_to_max_bval_map(a, b)

print(' '.join(str(aval_to_max_bval[x]) for x in a))
