#!/usr/bin/env python3

import itertools

def count_combos(coins, total):
    '''Solves the 0-1 coin change problem (coins must be increasing).'''
    memo = {}

    def count(tot, i):
        if tot == 0:
            return 1

        try:
            if coins[i] > tot:
                return 0
        except IndexError:
            return 0

        subproblem = (tot, i)
        try:
            return memo[subproblem]
        except KeyError:
            j = i + 1
            combos = count(tot, j) + count(tot - coins[i], j)
            memo[subproblem] = combos
            return combos

    return count(total, 0)

def all_powers(exponent):
    return (i**exponent for i in itertools.count(1))

def powers(exponent, bound):
    return itertools.takewhile(lambda y: y <= bound, all_powers(exponent))

for _ in range(int(input())):
    x, n = map(int, input().split())
    print(count_combos(list(powers(n, x)), x))
