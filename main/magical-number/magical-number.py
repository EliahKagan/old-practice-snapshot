#!/usr/bin/env python3

def count_magical_digits(s): # takes a str
    acc = 0
    
    for c in s:
        if c in '12':
            acc += 1
    
    return acc

def all_digits_magical(s): # takes a str
    return count_magical_digits(s) == len(s)

def is_magical_number(s):
    return all_digits_magical(str(count_magical_digits(s)))

for t in range(int(input())):
    print('YES' if is_magical_number(input().strip()) else 'NO')
