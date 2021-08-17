#!/usr/bin/env python3

def heapsort2(keys, values):
    '''Sorts keys in-place with heapsort, and reorders values accordingly.'''
    length = len(keys)
    if length != len(values):
        raise ValueError('keys and values must have the same length')

    if length < 2:
        return

    def swap(i, j):
        '''Swaps the specified positions in both keys and values.'''
        keys[i], keys[j] = keys[j], keys[i]
        values[i], values[j] = values[j], values[i]

    def order_ok(i, j):
        '''Tells if the key at i can precede the key at j in a maxheap.'''
        return keys[i] >= keys[j]

    def pick_child(start, stop):
        '''Picks the left or right child of start or None if neither exists.'''
        left = start * 2 + 1
        if left >= stop:
            return None

        right = left + 1
        return left if right == stop or order_ok(left, right) else right

    def heapify_down(start, stop):
        '''Sifts downward from start to stop to create a maxheap region.'''
        while True:
            child = pick_child(start, stop)
            if child is None or order_ok(start, child):
                break

            swap(start, child)
            start = child

    # Turn the data into a maxheap.
    for start in range(length // 2, -1, -1):
        heapify_down(start, length)

    # Extract elements from the maxheap and place them right to left.
    for stop in range(length - 1, 0, -1):
        swap(0, stop)
        heapify_down(0, stop)

# Unit test for heapsort2().
if __name__ == '__main__':
    def test(a):
        w = max(len(str(e)) for e in a)
        b = list(range(len(a)))

        def show():
            print()
            for e, i in zip(a, b):
                print('%*s %4d' % (w, e, i))

        heapsort2(a, b)
        show()
        heapsort2(b, a)
        show()

    test([10, 3, -1, 9, 56, 4, 22, 11, 10, 10, 14, -15, -2, -1, -8, 34, 33, 35])
    test(['foo', 'bar', 'baz', 'quux', 'Washington', 'foobar', 'Michigan'])
