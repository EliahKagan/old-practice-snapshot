#!/usr/bin/env python3

import itertools
import math

def read_val():
    return int(input())

def read_record():
    return map(int, input().split())

for _ in range(read_val()):
    v = read_val()
    vs = range(v)
    it = read_record()
    a = [list(itertools.islice(it, v)) for _ in vs]

    for k, i, j in itertools.product(vs, vs, vs):
        a[i][j] = min(a[i][j], a[i][k] + a[k][j])

    print(*itertools.chain.from_iterable(a))
