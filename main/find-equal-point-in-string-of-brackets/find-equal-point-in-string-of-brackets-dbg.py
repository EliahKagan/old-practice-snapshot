#!/usr/bin/env python3

def running_count(items, key):
    acc = 0

    for x in items:
        if x == key:
            acc += 1

        yield acc

def forward_running_count(items, key):
    return list(running_count(items, key))

def reverse_running_count(items, key):
    return list(running_count(items[::-1], key))[::-1]

def find_equal_point(expr):
    s = expr.strip() + '_' # non '(', ')' character allows after-end matches
    left = forward_running_count(s, '(')
    right = reverse_running_count(s, ')')

    for i, lc, rc in zip(range(len(s)), left, right):
        if lc == rc:
            print(i, lc)
            #return i

    return -1

for _ in range(int(input())):
    print(find_equal_point(input()))
