#!/usr/bin/env pypy3

"""
Counting swaps insertion sort would do, with recursive top-down mergesort.
https://www.hackerrank.com/challenges/ctci-merge-sort/problem
"""


def mergesort(a):
    """Recursively implemented top-down mergesort. Returns inversion count."""
    swaps = 0
    aux = []

    def merge(low, mid, high):
        nonlocal swaps
        assert not aux, 'auxiliary storage should be empty between merges'

        left = low
        right = mid

        # Merge elements until at least one side is exhausted.
        while left != mid and right != high:
            if a[right] < a[left]:
                swaps += mid - left
                aux.append(a[right])
                right += 1
            else:
                aux.append(a[left])
                left += 1

        # Copy over elements from whichever side (if any) still has them.
        aux.extend(a[i] for i in range(left, mid))
        aux.extend(a[i] for i in range(right, high))
        assert len(aux) == high - low, "aux should hold a full range"

        # Move everything back.
        a[low:high] = aux
        aux.clear()

    def mergesort_subarray(low, high):
        if high - low > 1:
            mid = (low + high) // 2
            mergesort_subarray(low, mid)
            mergesort_subarray(mid, high)
            merge(low, mid, high)

    mergesort_subarray(0, len(a))
    return swaps


def read_value():
    """Reads a single integer."""
    return int(input())


def read_record():
    """Reads a record of integers as a list."""
    n = read_value()
    a = list(map(int, input().split()))
    if len(a) != n:
        raise ValueError('wrong record length')
    return a


def run():
    """Reads multiple records and reports their inversion counts."""
    for _ in range(read_value()):
        a = read_record()
        print(mergesort(a))
        # assert a == sorted(a), 'the list should be correctly sorted'


if __name__ == '__main__':
    run()
