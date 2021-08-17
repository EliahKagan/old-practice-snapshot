#!/usr/bin/env python3

def count_valleys(trek):
    level = count = 0
    
    for step in trek:
        if step == 'U':
            level += 1
            if level == 0:
                count += 1
        elif step == 'D':
            level -= 1
        else:
            raise ValueError('unrecognized step')
    
    return count

length = int(input())
trek = input()

if len(trek) != length:
    raise ValueError('wrong number of steps')

print(count_valleys(trek))
