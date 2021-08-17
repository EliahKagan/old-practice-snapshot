#!/usr/bin/env python3

ASCENDING = 1
DESCENDING = 2
DESCENDING_ROTATED = 3
ASCENDING_ROTATED = 4

def read_values_with_rise_and_fall():
    input() # don't need n
    a = list(map(int, input().split()))
    
    rise = [i for i in range(1, len(a)) if a[i - 1] < a[i]]
    fall = [i for i in range(1, len(a)) if a[i - 1] > a[i]]
    
    return a, rise, fall

for t in range(int(input())):
    a, rise, fall = read_values_with_rise_and_fall()
    
    if len(fall) == 0:
        print(a[-1], ASCENDING)
    elif len(rise) == 0:
        print(a[0], DESCENDING)
    elif len(rise) == 1:
        print(a[rise[0]], DESCENDING_ROTATED)
    elif len(fall) == 1:
        print(a[fall[0] - 1], ASCENDING_ROTATED)
    else:
        raise ValueError('the input is not well-formed')
