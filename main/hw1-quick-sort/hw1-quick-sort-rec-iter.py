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


class Phase(object):
    """Phases for iteratively implemented recursive binary DFS."""
    GO_LEFT = object()
    GO_RIGHT = object()
    RETREAT = object()


class Frame(object):
    """A stack frame for iteratively implemented recursive quicksort."""

    __slots__ = ('_low', '_high', 'mid', 'phase')

    def __init__(self, low, high, phase):
        """Creates a stack frame for quicksorting the range [start, end)."""
        self._low = low
        self._high = high
        self.mid = None
        self.phase = phase

    @property
    def low(self):
        """Gets the left endpoint, which is inclusive."""
        return self._low

    @property
    def high(self):
        """Gets the right endpoint, which is exclusive."""
        return self._high


def quicksort(values):
    """
    Sorts a list of values via iteratively implemented recursive in-place
    quicksort.
    """
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

    stack = [Frame(0, len(values), Phase.GO_LEFT)]

    while stack:
        frame = stack[-1]

        if frame.phase is Phase.GO_LEFT:
            frame.mid = lomuto_partition(frame.low, frame.high)
            if maybe_unsorted(frame.low, frame.mid):
                stack.append(Frame(frame.low, frame.mid, Phase.GO_LEFT))
            frame.phase = Phase.GO_RIGHT
        elif frame.phase is Phase.GO_RIGHT:
            if maybe_unsorted(frame.mid, frame.high):
                stack.append(Frame(frame.mid, frame.high, Phase.GO_LEFT))
            frame.phase = Phase.RETREAT
        else:
            assert frame.phase is Phase.RETREAT, 'unrecognized phase'
            del stack[-1]


def run():
    """Reads input values, sorts them, and outputs the result."""
    a = read_input_values()
    quicksort(a)
    print '[%s]' % ','.join(str(x) for x in a)


if __name__ == '__main__':
    run()
