#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

total, length = read_record()
coins = list(read_record())

if len(coins) != length:
    raise ValueError('wrong record length')

memo = {} # (index, subtotal): count

def count_ways(index, subtotal):
    if subtotal == 0:
        return 1
    if index == length:
        return 0
    
    key = (index, subtotal)
    
    try:
        return memo[key]
    except KeyError:
        coin = coins[index]
        next_index = index + 1
        
        count = 0
        while subtotal >= 0:
            count += count_ways(next_index, subtotal)
            subtotal -= coin
        
        memo[key] = count
        return count

print(count_ways(0, total))
