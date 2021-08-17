#!/usr/bin/env python3


def read_value():
    """Reads a line of input as a single integer."""
    return int(input())


def read_record():
    """Reads a line of input as a whitespace-separated record of integers."""
    return map(int, input().split())


def read_input_values():
    """Reads input in the format specified in the problem description."""
    length = read_value()

    values = []
    while len(values) < length:
        values.extend(read_record())

    if len(values) != length:
        raise ValueError('wrong input length')

    return values


def heapsort(values):
    """Heapsorts a list of values in nondecreasing order."""
    def sift_up(child):
        while child > 0:
            parent = (child - 1) // 2
            if values[parent] >= values[child]:
                break
            values[parent], values[child] = values[child], values[parent]
            child = parent
