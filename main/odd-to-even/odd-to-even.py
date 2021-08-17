#!/usr/bin/env python3

def read_digits():
    return list(map(int, input().strip()))

def swap_even(digits):
    e = digits[-1]
    assert e % 2 != 0

    def swap(j):
        digits[-1], digits[j] = digits[j], digits[-1]

    for i in range(len(digits) - 1):
        if digits[i] % 2 == 0 and digits[i] < e:
            swap(i)
            return digits

    for i in range(len(digits) - 2, -1, -1):
        if digits[i] % 2 == 0:
            swap(i)
            return digits

    return digits

for _  in range(int(input())):
    print(*swap_even(read_digits()), sep='')
