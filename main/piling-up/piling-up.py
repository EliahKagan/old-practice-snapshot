#!/usr/bin/env python3

MAX_ITEM = 2**31

def can_peel(a):
    top = MAX_ITEM

    i = 0
    j = len(a) - 1

    while i <= j:
        if a[i] > a[j]:
            if a[i] > top:
                return False
            top = a[i]
            i += 1
        else:
            if a[j] > top:
                return False
            top = a[j]
            j -= 1

    return True

for _ in range(int(input())):
    input() # don't need n
    a = list(map(int, input().split()))
    print('Yes' if can_peel(a) else 'No')
