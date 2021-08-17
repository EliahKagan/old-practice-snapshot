#!/usr/bin/env python3

def listed(f):
    return lambda x: list(f(x))

def reversed_before_and_after(f):
    return lambda x: list(f(x[::-1]))[::-1]

@listed
def count_openers_before(s):
    acc = 0
    for c in s:
        yield acc
        if c == '(':
            acc += 1

@reversed_before_and_after
def count_closers_from(s):
    acc = 0
    for c in s:
        if c == ')':
            acc += 1
        yield acc

def find_equal_point(expr):
    s = expr.strip() + '_' # non '(', ')' character allows after-end matches
    left = count_openers_before(s)
    right = count_closers_from(s)

    for i, lc, rc in zip(range(len(s)), left, right):
        if lc == rc:
            return i

    return -1

for _ in range(int(input())):
    print(find_equal_point(input()))
