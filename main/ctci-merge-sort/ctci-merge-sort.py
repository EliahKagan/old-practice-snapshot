#!/usr/bin/env python3

def count_swaps(a):
    '''Sort a by mergesort and return the number of swaps.'''
    aux = [None] * len(a)

    def merge(lo, hi):
        mid = (lo + hi) // 2

        i = lo
        j = mid + 1
        k = lo

        swaps = 0
        while i <= mid and j <= hi: # merge from left and right sides
            if a[i] <= a[j]:
                aux[k] = a[i]
                i += 1
            else:
                swaps += j - k
                aux[k] = a[j]
                j += 1
            k += 1

        while i <= mid:     # merge any remaining from left
            aux[k] = a[i]
            i += 1
            k += 1

        while j <= hi:      # ...or any remaining from right
            aux[k] = a[j]
            j += 1
            k += 1

        while lo != k:      # copy back after merge
            a[lo] = aux[lo]
            lo += 1

        return swaps

    def mergesort(lo, hi):
        if lo >= hi:
            return 0

        mid = (lo + hi) // 2
        swaps = mergesort(lo, mid) + mergesort(mid + 1, hi)
        return swaps + merge(lo, hi)

    return mergesort(0, len(a) - 1)

for _ in range(int(input())):
    input() # don't need n
    print(count_swaps(list(map(int, input().split()))))
