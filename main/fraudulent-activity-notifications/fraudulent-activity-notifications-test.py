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

    print(f'window_size={window_size}')

    counts = [0] * (MAX_VALUE + 1)
    for day in range(window_size):
        counts[values[day]] += 1

    left_medial_count = (window_size + 1) // 2
    right_medial_count = window_size // 2 + 1
    assert 0 < left_medial_count <= right_medial_count <= left_medial_count + 1

    def compute_doubled_median():
        def count_to(target):
            nonlocal running_count, value
            while running_count < target:
                value += 1
                running_count += counts[value]
            return value

        running_count = 0
        value = -1
        left_medial_value = count_to(left_medial_count)
        right_medial_value = count_to(right_medial_count)
        return left_medial_value + right_medial_value

    doubled_median_fast = compute_doubled_median()

    values.sort()
    mid = window_size // 2
    doubled_median_slow = (values[mid] + values[mid - 1]
                            if window_size % 2 == 0
                            else values[mid] * 2)

    print(*values)
    print(f'fast={doubled_median_fast}, slow={doubled_median_slow}')
