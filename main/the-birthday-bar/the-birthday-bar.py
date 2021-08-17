#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def read_values():
    length = int(input())
    values = list(read_record())
    assert(len(values) == length)
    return values

def count_window_sums(values, window_width, target_sum):
    length = len(values)
    if length < window_width:
        return 0
    
    acc = sum(values[i] for i in range(window_width))
    count = 1 if acc == target_sum else 0
    
    start = 0
    end = window_width
    while end < length:
        acc += values[end] - values[start]
        if acc == target_sum:
            count += 1
        start += 1
        end += 1
    
    return count

values = read_values()
target_sum, window_width = read_record()

print(count_window_sums(values, window_width, target_sum))
