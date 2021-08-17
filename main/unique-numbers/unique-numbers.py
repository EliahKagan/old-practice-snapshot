#!/usr/bin/env python3

def get_unique_digit_numbers(m, n):
    xs = (str(k) for k in range(m, n + 1))
    return (x for x in xs if len(set(x)) == len(x))

for t in range(int(input())):
    print(*get_unique_digit_numbers(*map(int, input().split())))
