#!/usr/bin/env python3

def count_combos(coins, total):
    len_coins = len(coins)
    memo = {}

    def count(tot, i):
        if tot == 0:
            return 1

        if i == len_coins:
            return 0

        subproblem = (tot, i)
        try:
            return memo[subproblem]
        except KeyError:
            j = i + 1
            subtotals = range(0, total + 1, coins[i])
            combos = sum(count(tot - subtot, j) for subtot in subtotals)
            memo[subproblem] = combos
            return combos

    return count(total, 0)

def read_record():
    return map(int, input().split())

total, _ = read_record() # don't need m
coins = list(read_record())

print(count_combos(coins, total))
