#!/usr/bin/env python3

def read_values_with_rise_and_fall():
    input() # don't need n
    a = list(map(int, input().split()))

    rise = [i for i in range(1, len(a)) if a[i - 1] < a[i]]
    fall = [i for i in range(1, len(a)) if a[i - 1] > a[i]]

    return a, rise, fall

for t in range(int(input())):
    a, rise, fall = read_values_with_rise_and_fall()
    
    if (len(a) < 2):
        raise ValueError('an array with < 2 elements has no inversions')
    
    if (len(a) == 2):
        print(*a[::-1])
    elif len(fall) == 2:
        print(*sorted(a))
    elif len(rise) == 2:
        print(*sorted(a, reverse=True))
    else:
        print('-1')
