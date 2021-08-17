#!/usr/bin/env python3

from functools import reduce
from operator import lt, gt

def count_running_optima(comp, items):
    def combine(acc, cur):
        count, best = acc
        return (count + 1, cur) if comp(best, cur) else (count, best)
    
    head, *tail = items
    count, best = reduce(combine, tail, (0, head))
    return count

input() # don't need n
s = list(map(int, input().split()))

count_max = count_running_optima(lt, s)
count_min = count_running_optima(gt, s)
print(count_max, count_min)
