#!/usr/bin/env python3

import functools

def count_ways(coins, total):
    length = len(coins)

    @functools.lru_cache(maxsize=None)
    def _solve(index, subtot):
        value = coins[index]

        return sum(solve(index + 1, next_subtot)
                   for next_subtot in range(subtot, -1, -value))

    def solve(index, subtot):
        if subtot == 0:
            return 1
        if index == length:
            return 0
        return _solve(index, subtot)

    return solve(0, total)

def read_record(length):
    ret = list(map(int, input().split()))
    if len(ret) != length:
        raise ValueError('wrong record length')
    return ret

def run():
    total, length = read_record(2)
    coins = read_record(length)
    print(count_ways(coins, total))

if __name__ == '__main__':
    run()
