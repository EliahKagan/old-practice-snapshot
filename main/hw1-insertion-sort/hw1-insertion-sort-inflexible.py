#!/usr/bin/env python2


def read_record():
    """Reads a line of input as a list of integers."""
    length = int(raw_input())
    record = map(int, raw_input().split())
    if len(record) != length:
        raise ValueError('wrong record length')
    return record


def insertion_sort(a):
    """Sorts the list, a, with insertion sort."""
    for right in xrange(1, len(a)):
        for left in xrange(right, 0, -1):
            if a[left - 1] <= a[left]:
                break
            a[left - 1], a[left] = a[left], a[left - 1]


def run():
    """Reads input values, sorts them, and outputs the result."""
    a = read_record()
    insertion_sort(a)
    print '[%s]' % ','.join(str(x) for x in a)


if __name__ == '__main__':
    run()
