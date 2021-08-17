#!/usr/bin/env pypy3

"""
Counting swaps insertion sort would do, with iteratively implemented recursive
top-down mergesort.
https://www.hackerrank.com/challenges/ctci-merge-sort/problem
"""

import enum


@enum.unique
class Action(enum.Enum):
    """Phases for solving binary-tree-like divide-and-conquer problems."""
    GO_LEFT = 0
    GO_RIGHT = 1
    RETREAT = 2


class Frame:  # pylint: disable=too-few-public-methods
    """Stack frame structure for simulating recursive top-down mergesort."""
    __slots__ = ('low', 'high', 'action')

    def __init__(self, low, high):
        """Makes a stack frame for left-to-right mergesort of [low, high)."""
        self.low = low
        self.high = high
        self.action = Action.GO_LEFT


def maybe_unsorted(low, high):
    """Tells if a half-open interval is big enough to possibly be unsorted."""
    return high - low > 1


def midpoint(low, high):
    """Gets an index nearest to the midpoint of a half-open interval."""
    return (high + low) // 2


def mergesort(a):
    """
    Iteratively implemented recursive top-down mergesort.
    Returns inversion count.
    """
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

    stack = []

    def schedule(low, high):
        if maybe_unsorted(low, high):
            stack.append(Frame(low, high))

    schedule(0, len(a))
    while stack:
        frame = stack[-1]

        if frame.action == Action.GO_LEFT:
            frame.action = Action.GO_RIGHT
            schedule(frame.low, midpoint(frame.low, frame.high))
        elif frame.action == Action.GO_RIGHT:
            frame.action = Action.RETREAT
            schedule(midpoint(frame.low, frame.high), frame.high)
        else:
            assert frame.action == Action.RETREAT
            merge(frame.low, midpoint(frame.low, frame.high), frame.high)
            del stack[-1]

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
