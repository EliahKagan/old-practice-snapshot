#!/usr/bin/env python3

def heapsort(a):
    stop = len(a)
    if stop < 2:
        return

    def swap(i, j):
        a[i], a[j] = a[j], a[i]

    def order_ok(i, j):
        return a[i] >= a[j]

    def pick_child(start):  # at the lowest level, returns None
        left_child = start * 2 + 1
        if left_child >= stop:
            return None

        right_child = left_child + 1

        if right_child == stop or order_ok(left_child, right_child):
            return left_child

        return right_child

    def heapify_down(start):
        while True:
            child = pick_child(start)
            if child is None or order_ok(start, child):
                break
            swap(start, child)
            start = child

    # Turn the array into a maxheap.
    for i in range(stop // 2, -1, -1):
        heapify_down(i)

    # Extract each element, placing them from right to left.
    while stop != 1:
        stop -= 1
        swap(0, stop)
        heapify_down(0)

if __name__ == '__main__':
    a = [10, 3, -1, 9, 56, 4, 22, 11, 10, 10, 14, -15, -2, -1, -8, 34, 33, 35, -16]
    heapsort(a)
    print(a)

    b = []
    heapsort(b)
    print(b)

    c = [3]
    heapsort(c)
    print(c)

    d = ["foo", "bar", "baz", "quux", "Washington", "foobar", "Michigan"]
    print(sorted(d))
    heapsort(d)
    print(d)
