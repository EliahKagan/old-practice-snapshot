#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def is_class_canceled(arrivals, needed):
    return sum(1 for time in arrivals if time <= 0) < needed

for _ in range(int(input())):
    _, needed = read_record()
    arrivals = read_record()
    print('YES' if is_class_canceled(arrivals, needed) else 'NO')
