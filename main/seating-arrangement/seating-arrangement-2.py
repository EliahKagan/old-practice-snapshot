#!/usr/bin/env python3

SEATS = ('WS', 'MS', 'AS', 'AS', 'MS', 'WS') # 0-based seating chart, mod 6
ROW_LEN = len(SEATS)
POD_LEN = ROW_LEN * 2
POD_MAX = POD_LEN - 1

def iround(value, interval):
    '''Rounds value to the nearest number expressible as (k * interval).'''
    return value // interval * interval

def get_seat_type(n): # uses 1-based indexing
    return SEATS[(n - 1) % len(SEATS)]

def get_facing_seat(n): # uses 1-based indexing
    k = n - 1
    return iround(k, POD_LEN) + (POD_MAX - k % POD_LEN) + 1

for _ in range(int(input())):
    n = int(input())
    print(get_facing_seat(n), get_seat_type(n))
