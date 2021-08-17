#!/usr/bin/env python2


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


def maybe_unsorted(low, high):
    """Tells if a range is big enough to potentially be unsorted."""
    return high - low > 1


def quicksort(values):
    """Sorts a list of values via iterative in-place quicksort."""
    def lomuto_partition(low, high):
        mid = (low + high) // 2
        values[low], values[mid] = values[mid], values[low]
        pivot = values[low]

        left = low
        for right in xrange(low + 1, high):
            if values[right] < pivot:
                left += 1
                values[left], values[right] = values[right], values[left]

        values[low], values[left] = values[left], values[low]
        return left

    if not maybe_unsorted(0, len(values)):
        return
    stack = [(0, len(values))]

    while stack:
        low, high = stack.pop()
        mid = lomuto_partition(low, high)
        if maybe_unsorted(mid + 1, high):
            stack.append((mid + 1, high))
        if maybe_unsorted(low, mid):
            stack.append((low, mid))


def run():
    """Reads input values, sorts them, and outputs the result."""
    a = read_input_values()
    quicksort(a)
    print '[%s]' % ','.join(str(x) for x in a)


if __name__ == '__main__':
    run()
