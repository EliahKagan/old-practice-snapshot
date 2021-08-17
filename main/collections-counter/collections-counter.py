#!/usr/bin/env python3

from collections import Counter

def read_record():
    return map(int, input().split())

input() # don't need X
stock = Counter(read_record())
profit = 0

for _ in range(int(input())):
    size, price = read_record()
    if stock[size] != 0:
        stock[size] -= 1
        profit += price

print(profit)
