#!/usr/bin/env python2

#coins= [1, 2, 5] 
#amount = 5
coins = [11, 24, 37, 50, 63, 76, 89, 102]
amount = 5000

length = len(coins)
memo = {}

def ways(subtot, index):
    if subtot == 0:
        return 1
    
    if index == length:
        return 0
    
    key = (subtot, index)
    try:
        return memo[key]
    except KeyError:
        value = coins[index]
        index += 1
        count = 0

        while subtot >= 0:
            count += ways(subtot, index)
            subtot -= value
        
        memo[key] = count
        return count

print ways(amount, 0)
