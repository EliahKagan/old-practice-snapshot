#!/usr/bin/env python3

def divisible_by_9(digits):
    return sum(int(d) for d in digits) % 9 == 0

def divisible_by_4(digits):
    return int(digits[-2::]) % 4 == 0

for t in range(int(input())):
    digits = input().strip()
    print('1' if divisible_by_9(digits) and divisible_by_4(digits) else '0')
