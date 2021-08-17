#!/usr/bin/env python3

from collections import Counter
from heapq import heapify, heappop, heappush

def get_neg_freqs(xs):
    return [-posf for posf in Counter(xs).values()]

def get_neg_freq_heap(xs):
    heap = get_neg_freqs(xs)
    heapify(heap)
    return heap

def diminish_top(heap):
    top = heappop(heap) + 1
    if top != 0:
        assert top < 0
        heappush(heap, top)

def diminish_top_repeatedly(heap, k):
    for _ in range(k):
        if len(heap) == 0:
            break
        diminish_top(heap)

def compute_square_sum(ys):
    return sum(y * y for y in ys)

def minimize_freq_square_sum(xs, k):
    '''Minimal square sum of frequencies of items in xs after <= k removals.'''
    heap = get_neg_freq_heap(xs)
    diminish_top_repeatedly(heap, k)
    return compute_square_sum(heap)

def read_val():
    return int(input())

for _ in range(read_val()):
    xs = input().strip()
    k = read_val()
    print(minimize_freq_square_sum(xs, k))
