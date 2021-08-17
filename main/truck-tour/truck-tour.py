#!/usr/bin/env python3

NO_SOLUTION = -1

def read_deltas():
    for _ in range(int(input())):
        x, y = map(int, input().split())
        yield x - y

def do_first_pass(deltas):
    total_sum = min_partial_sum = 0

    for delta in deltas:
        total_sum += delta
        min_partial_sum = min(min_partial_sum, total_sum)

    return total_sum, min_partial_sum

def get_best_start_index(deltas):
    total_sum, min_partial_sum = do_first_pass(deltas)

    if total_sum < 0:
        return NO_SOLUTION

    for index, delta in enumerate(deltas):
        if min_partial_sum >= 0:
            break
        min_partial_sum -= delta

    if index == len(deltas):
        raise ValueError('internal error: no solution, but there should be')

    return index

print(get_best_start_index(list(read_deltas())))
