#!/usr/bin/env python3

from collections import defaultdict

def get_connected_components(a):
    val_to_comp = defaultdict(set)
    idx_to_comp = {} # maps i to set of adjacent indices (and itself)

    for i in range(len(a)):
        comp = val_to_comp[a[i]]
        comp.add(i)
        idx_to_comp[i] = comp

    return idx_to_comp

def get_max_bval_mapper(idx_to_comp, b):
    compid_to_bval = {}
    for comp in idx_to_comp.values():
        compid_to_bval[id(comp)] = max(b[i] for i in comp)

    return lambda i: compid_to_bval[id(idx_to_comp[i])]

def get_record():
    return list(map(int, input().split()))

n = int(input())
a = get_record()
b = get_record()
assert(len(a) == len(b) == n)

get_max_bval = get_max_bval_mapper(get_connected_components(a), b)
print(*(get_max_bval(i) for i in range(n)))
