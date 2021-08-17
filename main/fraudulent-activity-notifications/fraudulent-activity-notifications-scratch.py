#!/usr/bin/env pypy3

MAX_EXPENDITURE = 200

def read_record():
    return map(int, input().split())

total_count, window_size = read_record()
expenditures = list(read_record())
if len(expenditures) != total_count:
    raise ValueError('wrong number of expenditures')

counts = [0] * (MAX_EXPENDITURE + 1) # counts of each expenditure

for i in range(window_size):
    counts[expenditures[i]] += 1

half_count = window_size // 2
left_count = 0
mid = 0



##
for mid in range(1, len(counts)):
    left_count += counts[mid]