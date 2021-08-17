#!/usr/bin/env python3

from itertools import chain

def read_record():
    return map(int, input().split())

def quads_with_sum(a, k):
    a = sorted(a)
    n = len(a)
    if n < 4:
        return

    gval = None

    for g in range(n - 3):
        if a[g] == gval:
            continue

        gval = a[g]
        hij_target = k - gval
        hval = None

        for h in range(g + 1, n - 2):
            if a[h] == hval:
                continue

            hval = a[h]
            ij_target = hij_target - hval
            i = h + 1
            j = n - 1

            while i < j:
                ival = a[i]
                jval = a[j]
                ij_sum = ival + jval

                if ij_sum == ij_target:
                    yield gval, hval, ival, jval

                if ij_sum <= ij_target:
                    while a[i] == ival and i < j:
                        i += 1

                if ij_sum >= ij_target:
                    while a[j] == jval and i < j:
                        j -= 1

for _ in range(int(input())):
    _, k = read_record() # don't need n
    quads = list(quads_with_sum(read_record(), k))
    if quads:
        for quad in quads:
            print (*quad, end=' $')
        print()
    else:
        print('-1')
