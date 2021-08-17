#!/usr/bin/env python3

import heapq

class MinHeap(object):
    def __init__(self):
        self._elems = []

    def __len__(self):
        return len(self._elems)

    def push(self, elem):
        heapq.heappush(self._elems, elem)

    def pop(self):
        return heapq.heappop(self._elems)

    def peek(self):
        return self._elems[0]

class MaxHeap(object):
    def __init__(self):
        self._elems = []

    def __len__(self):
        return len(self._elems)

    def push(self, elem):
        heapq.heappush(self._elems, -elem)

    def pop(self):
        return -heapq.heappop(self._elems)

    def peek(self):
        return -self._elems[0]

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
