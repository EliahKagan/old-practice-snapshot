#!/usr/bin/env python3
# to test some code from fraudulent-activity-notifications.py

import itertools

MAX_VALUE = 200

def read_record(): # read a record as a list; exit if it's empty or ill-formed
    try:
        record = list(map(int, input('> ').split()))
        if record:
            return record
    except ValueError:
        pass
    exit()

while True:
    values = read_record()
    window_size = len(values)

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

        # this is for debugging and was not present in the original file
        print(f'runnning_count={running_count}, midpoint={midpoint}')

        if window_size % 2 != 0 or running_count != midpoint:
            return value * 2

        for low_value in itertools.count(value - 1, -1):
            assert low_value >= 0
            if counts[low_value] != 0:
                break

        return value + low_value

    doubled_median_fast = compute_doubled_median()

    values.sort()
    mid = window_size // 2
    doubled_median_slow = (values[mid] + values[mid - 1]
                            if window_size % 2 == 0
                            else values[mid] * 2)

    print(*values)
    print(f'fast={doubled_median_fast}, slow={doubled_median_slow}')
