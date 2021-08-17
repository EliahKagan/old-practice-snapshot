#!/usr/bin/env python3

def divisible_by_11(digits):
    acc = 0
    
    sign = 1
    for d in digits:
        acc += int(d) * sign
        sign *= -1
    
    return acc % 11 == 0

for t in range(int(input())):
    print('1' if divisible_by_11(input().strip()) else '0')
