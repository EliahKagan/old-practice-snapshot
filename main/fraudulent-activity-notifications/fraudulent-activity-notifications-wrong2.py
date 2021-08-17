#!/usr/bin/env pypy3

import itertools

MAX_VALUE = 200

def read_record():
    return map(int, input().split())

total_count, window_size = read_record()
values = list(read_record())
assert 0 < window_size <= total_count == len(values)

counts = [0] * (MAX_VALUE + 1)
for day in range(window_size):
    counts[values[day]] += 1

midpoint = window_size // 2 + 1

def compute_doubled_median():
    running_count = 0
    for value in itertools.count():
        running_count += counts[value]
        if running_count >= midpoint:
            break

    if window_size % 2 != 0 or running_count != midpoint:
        return value * 2

    for low_value in itertools.count(value - 1, -1):
        assert low_value >= 0
        if counts[low_value] != 0:
            break

    return value + low_value

notifications = 0
for day in range(window_size, total_count):
    # check today's value against the median _before_ sliding the window right
    if values[day] >= compute_doubled_median():
        notifications += 1

    # update counts for the effect of sliding the window to the right
    counts[values[day]] += 1
    counts[values[day - window_size]] -= 1

print(notifications)
