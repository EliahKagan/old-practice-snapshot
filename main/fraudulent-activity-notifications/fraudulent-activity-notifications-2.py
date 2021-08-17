#!/usr/bin/env pypy3

MAX_VALUE = 200

def read_record():
    return map(int, input().split())

total_count, window_size = read_record()
values = list(read_record())
assert 0 < window_size <= total_count == len(values)

min_value = min(values)
assert 0 <= min_value

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
    value = min_value - 1 # the initial increment will index the initial count
    left_medial_value = count_to(left_medial_count)
    right_medial_value = count_to(right_medial_count)
    return left_medial_value + right_medial_value

notifications = 0
for day in range(window_size, total_count):
    # check today's value against the median _before_ sliding the window right
    if values[day] >= compute_doubled_median():
        notifications += 1

    # update counts for the effect of sliding the window to the right
    counts[values[day]] += 1
    counts[values[day - window_size]] -= 1

print(notifications)
