#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

total, length = read_record()
coins = list(read_record())

if len(coins) != length:
    raise ValueError('wrong record length')

ways = [[1] + [0] * total for _ in range(length + 1)] # ways[index][subtotal]

for index in range(length - 1, -1, -1):
    for subtotal in range(total, -coins[index], 0):
        ways[index][subtotal] += ways[index + 1][]

    for subtotal in range(coins[index], coins[index], total + 1):
