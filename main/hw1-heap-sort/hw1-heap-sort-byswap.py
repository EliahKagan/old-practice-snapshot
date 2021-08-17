#!/usr/bin/env python3


def read_value():
    """Reads a line of input as a single integer."""
    return int(input())


def read_record():
    """Reads a line of input as a whitespace-separated record of integers."""
    return map(int, input().split())


def read_input_values():
    """Reads input in the input format specified in the problem description."""
    length = read_value()

    values = []
    while len(values) < length:
        values.extend(read_record())

    if len(values) != length:
        raise ValueError('wrong input length')

    return values


def display_values(values):
    """Prints values in the output format given in the problem description."""
    print(f'[{",".join(map(str, values))}]')


def heapsort(values):
    """Heapsorts a list of values in nondecreasing order."""
    length = len(values)

    def pick_child(parent):
        left = parent * 2 + 1
        if left >= length:
            return None

        right = left + 1
        if right == length or values[left] >= values[right]:
            return left

        return right

    def sift_down(parent):
        while True:
            child = pick_child(parent)
            if child is None or values[parent] >= values[child]:
                break

            values[parent], values[child] = values[child], values[parent]
            parent = child

    # Convert the list into a maxheap.
    for parent in range(length // 2, -1, -1):
        sift_down(parent)

    # Extract each element from the maxheap, placing them from right to left.
    while length > 1:
        length -= 1
        values[0], values[length] = values[length], values[0]
        sift_down(0)


def run():
    """Reads the input values, heapsorts them, and displays the results."""
    values = read_input_values()
    heapsort(values)
    display_values(values)


if __name__ == '__main__':
    run()
