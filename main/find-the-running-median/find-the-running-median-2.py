#!/usr/bin/env python3

class MinHeap(object):
    def __init__(self):
        self._elems = []

    def __len__(self):
        return len(self._elems)

    def peek(self):
        return self._elems[0]

    def pop(self):
        value = self._elems[0]

        self._elems[0] = self._elems[-1]
        del self._elems[-1]
        self._heapify_down()

        return value

    def push(self, value):
        self._elems.append(value)
        self._heapify_up()

    def _swap(self, i, j):
        self._elems[i], self._elems[j] = self._elems[j], self._elems[i]

    def _heapify_down(self):
        length = len(self)
        current_index = 0

        while True:
            left_child_index = current_index * 2 + 1
            if left_child_index >= length:
                break

            right_child_index = left_child_index + 1
            if (right_child_index < length and self._elems[right_child_index]
                                             < self._elems[left_child_index]):
                child_index = right_child_index
            else:
                child_index = left_child_index

            if self._elems[current_index] <= self._elems[child_index]:
                break

            self._swap(current_index, child_index)
            current_index = child_index

    def _heapify_up(self):
        current_index = len(self) - 1

        while current_index != 0:
            parent_index = (current_index - 1) // 2
            if self._elems[parent_index] <= self._elems[current_index]:
                break

            self._swap(current_index, parent_index)
            current_index = parent_index

class MaxHeap(object):
    def __init__(self):
        self._heap = MinHeap()

    def __len__(self):
        return len(self._heap)

    def peek(self):
        return -self._heap.peek()

    def pop(self):
        return -self._heap.pop()

    def push(self, value):
        return self._heap.push(-value)

low = MaxHeap()
high = MinHeap()

def add(e):
    (low if e < low.peek() else high).push(e)

def rebalance():
    d = len(low) - len(high)
    if d == 2:
        high.push(low.pop())
    elif d == -2:
        low.push(high.pop())

def compute_median():
    d = len(low) - len(high)
    if d == 0:
        return (low.peek() + high.peek()) / 2.0
    else:
        return (low if d > 0 else high).peek()

def display(value):
    print('%.1f' % value)

def get():
    return int(input())

n = get()

low.push(get())
display(low.peek())

for _ in range(1, n):
    add(get())
    rebalance()
    display(compute_median())
