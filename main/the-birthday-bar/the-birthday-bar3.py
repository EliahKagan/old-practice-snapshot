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
    
    for j in range(window_width, length):
        acc += values[j] - values[j - window_width]
        if acc == target_sum:
            count += 1
    
    return count

values = read_values()
target_sum, window_width = read_record()

print(count_window_sums(values, window_width, target_sum))
