#!/usr/bin/env python3

VOWELS = 'aeiou'

def swap(a, i, j):
    tmp = a[i]
    a[i] = a[j]
    a[j] = tmp

def reverse_vowels(a):
    i = 0
    j = len(a) - 1
    
    while i < j:
        if a[i] not in VOWELS:
            i += 1
        elif a[j] not in VOWELS:
            j -= 1
        else:
            swap(a, i, j)
            i += 1
            j -= 1

for _ in range(int(input())):
    a = list(input().strip())
    reverse_vowels(a)
    print(''.join(a))
