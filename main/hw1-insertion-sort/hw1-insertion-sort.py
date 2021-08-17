#!/usr/bin/env python2

import sys


def read_value():
    """Reads a line of input as a single integer."""
    return int(raw_input())


def read_record():
    """Reads a line of input as a list of integers."""
    return map(int, raw_input().split())


def read_input_values():
    """Reads a line of input as a list of integers."""
    length = read_value()

    values = []
    while len(values) < length:
        values.extend(read_record())

    if len(values) != length:
        raise ValueError('wrong input length')
    return values


def insertion_sort(values):
    """Sorts a list of values via insertion sort."""
    for right in xrange(1, len(values)):
        for left in xrange(right, 0, -1):
            if values[left - 1] <= values[left]:
                break
            values[left - 1], values[left] = values[left], values[left - 1]


def run():
    """Reads input values, sorts them, and outputs the result."""
    a = read_input_values()
    insertion_sort(a)
    print '[%s]' % ','.join(str(x) for x in a)


if __name__ == '__main__':
    run()
