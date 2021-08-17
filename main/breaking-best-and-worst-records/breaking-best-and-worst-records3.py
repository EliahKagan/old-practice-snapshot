#!/usr/bin/env python3

from operator import lt, gt

def count_running_optima(comp, items):
    best, *tail = items
    count = 0
    
    for cur in tail:
        if comp(best, cur):
            best = cur
            count += 1

    return count

input() # don't need n
s = list(map(int, input().split()))

count_max = count_running_optima(lt, s)
count_min = count_running_optima(gt, s)
print(count_max, count_min)
