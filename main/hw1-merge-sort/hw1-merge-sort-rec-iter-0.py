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


def maybe_unsorted(start, end):
    """Tells if a range is big enough to potentially be unsorted."""
    return end - start > 1


class Phase(object):
    """Phases for iteratively implemented recursive binary DFS."""
    GO_LEFT = 1
    GO_RIGHT = 2
    RETREAT = 3


class Frame(object):
    """A stack frame for iteratively implemented recursive mergesort."""

    __slots__ = ('_start', '_end', 'phase')

    def __init__(self, start, end, phase):
        """Creates a stack frame for mergesorting the range [start, end)."""
        self._start = start
        self._end = end
        self.phase = phase

    @property
    def start(self):
        """Gets the left endpoint, which is inclusive."""
        return self._start

    @property
    def end(self):
        """Get the right endpoint, which is exclusive."""
        return self._end

    @property
    def mid(self):
        """Gets the midpoint of the range."""
        return (self._start + self._end) // 2


def mergesort(values):
    """
    Sorts a list of values via iteratively implemented recursive top-down
    mergesort.
    """
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


    if not maybe_unsorted(0, len(values)):
        return

    stack = [Frame(0, len(values), Phase.GO_LEFT)]

    while stack:
        frame = stack[-1]

        if frame.phase is Phase.GO_LEFT:
            if maybe_unsorted(frame.start, frame.mid):
                stack.append(Frame(frame.start, frame.mid, Phase.GO_LEFT))
            frame.phase = Phase.GO_RIGHT
        elif frame.phase is Phase.GO_RIGHT:
            if maybe_unsorted(frame.mid, frame.end):
                stack.append(Frame(frame.mid, frame.end, Phase.GO_LEFT))
            frame.phase = Phase.RETREAT
        else:
            assert frame.phase is Phase.RETREAT, 'unrecognized phase'
            merge(frame.start, frame.mid, frame.end)
            del stack[-1]


def run():
    """Reads input values, sorts them, and outputs the result."""
    a = read_input_values()
    mergesort(a)
    print '[%s]' % ','.join(str(x) for x in a)


if __name__ == '__main__':
    run()
