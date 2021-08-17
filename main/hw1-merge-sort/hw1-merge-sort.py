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


def mergesort(values):
    """Sorts a list of values via iterative bottom-up mergesort."""
    aux = []
    def merge(start, mid, end):
        left = start
        right = mid

        while left < mid and right < end:
            if values[right] < values[left]:
                aux.append(values[right])
                right += 1
            else:
                aux.append(values[left])
                left += 1

        aux.extend(values[left:mid])
        values[start:right] = aux
        aux[:] = ()

    delta = 1  # length of [start, mid)
    while delta < len(values):
        for start in xrange(0, len(values) - delta, delta * 2):
            mid = start + delta
            end = min(mid + delta, len(values))
            merge(start, mid, end)

        delta *= 2


def run():
    """Reads input values, sorts them, and outputs the result."""
    a = read_input_values()
    mergesort(a)
    print '[%s]' % ','.join(str(x) for x in a)


if __name__ == '__main__':
    run()
