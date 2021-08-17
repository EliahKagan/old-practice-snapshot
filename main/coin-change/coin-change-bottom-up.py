#!/usr/bin/env python

def read_record():
    return map(int, input().split())

total, length = read_record()
coins = list(read_record())

if len(coins) != length:
    raise ValueError('wrong record length')

ways = [1] + [0] * total

for coin in coins:
    for subtot in range(coin, total + 1):
        # with any combination of previous coins and at least one of this one
        ways[subtot] += ways[subtot - coin]

print(ways[total])
