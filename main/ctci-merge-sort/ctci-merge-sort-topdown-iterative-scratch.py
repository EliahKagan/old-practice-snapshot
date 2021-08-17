#!/usr/bin/env python3

"""
Counting swaps insertion sort would do, with iterative top-down mergesort.
https://www.hackerrank.com/challenges/ctci-merge-sort/problem
"""


def maybe_unsorted(low, high):
    """Tells if a half-open interval is big enough to possibly be unsorted."""
    return high - low > 1


def midpoint(low, high):
    """Gets an index nearest to the midpoint of a half-open interval."""
    return (high + low) // 2


def mergesort(a):
    """Iteratively implemented top-down mergesort. Returns inversion count."""
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
        assert len(aux) == high - low, 'aux should hold a full range'

        # Move everything back.
        a[low:high] = aux
        aux.clear()

    def mergesort_impl(low, high):
        last_low = last_high = high  # starts as a "null" (empty) interval

        stack = []
        while maybe_unsorted(low, high) or stack:
            # Traverse left as far as possible.
            while maybe_unsorted(low, high):
                stack.append((low, high))
                high = midpoint(low, high)

            cur_low, cur_high = stack[-1]
            cur_mid = midpoint(cur_low, cur_high)

            if maybe_unsorted(cur_mid, cur_high) and (cur_mid != last_low or
                                                      cur_high != last_high):
                # We can traverse right but haven't yet, so do so.
                low = cur_mid
                high = cur_high
            else:
                # The right subinterval is sorted, so merge and retreat.
                merge(cur_low, cur_mid, cur_high)
                last_low = cur_low
                last_high = cur_high
                del stack[-1]

    mergesort_impl(0, len(a))
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
        assert a == sorted(a), 'the list should be correctly sorted'


if __name__ == '__main__':
    run()
