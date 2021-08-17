#!/usr/bin/env python3

MULTIPLIER = 10**8

def get_record():
    input() # don't need n
    return input().split()

def compute_weight(digits):
    return sum(1 for ch in digits if ch == '0') * MULTIPLIER + int(digits)

for _ in range(int(input())):
    result = max(get_record(), key=compute_weight)
    print(result if '0' in result else '-1')
