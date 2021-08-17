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


def midpoint(start, end):
    """Gives the midpoint of a range."""
    return (start + end) // 2


def mergesort(values):
    """Sorts a list of values via iterative top-down mergesort."""
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


    def do_mergesort(start, end):
        last_start = last_end = None
        stack = []

        while maybe_unsorted(start, end) or stack:
            # Go left as far as possible.
            while maybe_unsorted(start, end):
                stack.append((start, end))
                end = midpoint(start, end)

            cur_start, cur_end = stack[-1]
            cur_mid = midpoint(cur_start, cur_end)

            if (maybe_unsorted(cur_mid, cur_end)
                    and (cur_mid != last_start or cur_end != last_end)):
                # We can go right but haven't. Do that.
                #stack.append((cur_mid, cur_end))
                start = cur_mid
                end = cur_end
            else:
                # We already went right or didn't have to. Merge and retreat.
                merge(cur_start, cur_mid, cur_end)
                last_start = cur_start
                last_end = cur_end
                del stack[-1]

    do_mergesort(0, len(values))


def run():
    """Reads input values, sorts them, and outputs the result."""
    a = read_input_values()
    mergesort(a)
    print '[%s]' % ','.join(str(x) for x in a)


if __name__ == '__main__':
    run()
