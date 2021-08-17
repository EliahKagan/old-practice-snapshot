#!/usr/bin/env python3

SEATS = ('WS', 'MS', 'AS', 'AS', 'MS', 'WS') # 0-based seating chart, mod 6
ROW_LEN = len(SEATS)

FACING = (11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0) # 0-based facing map, mod 12
POD_LEN = len(FACING)

def iround(value, interval):
    '''Rounds value to the nearest number expressible as (k * interval).'''
    return value // interval * interval

def get_seat_type(n): # uses 1-based indexing
    return SEATS[(n - 1) % len(SEATS)]

def get_facing_seat(n): # uses 1-based indexing
    k = n - 1
    return iround(k, POD_LEN) + FACING[k % POD_LEN] + 1

for _ in range(int(input())):
    n = int(input())
    print(get_facing_seat(n), get_seat_type(n))
