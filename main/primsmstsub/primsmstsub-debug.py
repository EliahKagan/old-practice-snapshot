#!/usr/bin/env python3

from collections import namedtuple
from itertools import chain, repeat
from math import inf

class PrimHeap:
    class Entry:
        def __init__(self, key, value):
            self.key = key
            self.value = value

        def __repr__(self):
            return '%s=>%s' % (self.key, self.value)

    def __init__(self, min_key, max_key):
        # initialize the (key, value) entries
        key_range = range(min_key, max_key + 1)
        self._entries = [self.Entry(key, inf) for key in key_range]

        # initialize the key=>index mappings
        index_range = range(len(self))
        self._map = list(chain(repeat(None, min_key), index_range))

    def __bool__(self):
        return bool(self._entries)

    def __len__(self):
        return len(self._entries)

    def pop(self):
        ret = self._entries[0]
        self._map[ret.key] = None

        if len(self) == 1:
            self._entries.clear()
        else:
            self._entries[0] = self._entries.pop()
            self._sift_down(0)

        return ret

    def contains(self, key):
        return self._map[key] is not None

    def decrease(self, key, value):
        child = self._map[key]
        entry = self._entries[child]

        if value < entry.value:
            entry.value = value
            self._sift_up(child)

    def _sift_up(self, child):
        while child != 0:
            parent = (child - 1) // 2
            if self._order_ok(parent, child):
                break

            self._swap(child, parent)
            child = parent

        self._record(child)

    def _sift_down(self, parent):
        while True:
            child = self._pick_child(parent)
            if child is None or self._order_ok(parent, child):
                break

            self._swap(parent, child)
            parent = child

        self._record(parent)

    def _pick_child(self, parent):
        size = len(self)

        left = parent * 2 + 1
        if left >= len(self):
            return None

        right = left + 1
        return left if right == size or self._order_ok(left, right) else right

    def _swap(self, src, dest):
        ents = self._entries
        ents[dest], ents[src] = ents[src], ents[dest]
        self._record(src)

    def _record(self, src):
        self._map[self._entries[src].key] = src

    def _order_ok(self, parent, child):
        return self._entries[parent].value <= self._entries[child].value

Edge = namedtuple('Edge', 'vertex weight')

def add_edge(adj, u, v, wt):
    adj[u].append(Edge(v, wt))
    adj[v].append(Edge(u, wt))

FIRST_VERTEX = 1

def read_record():
    return map(int, input().split())

def read_graph():
    vertex_count, edge_count = read_record()

    adj = [[] for _ in range(FIRST_VERTEX + vertex_count)]
    for _ in range(edge_count):
        add_edge(adj, *read_record())

    return adj

def calculate_mst_weight(adj, start):
    total_cost = 0

    cost_heap = PrimHeap(FIRST_VERTEX, len(adj) - 1)
    cost_heap.decrease(start, 0)

    while cost_heap:
        ent = cost_heap.pop()
        total_cost += ent.value

        print('DEBUG:', ent) # FIXME: remove after debugging
        for edge in adj[ent.key]:
            if cost_heap.contains(edge.vertex):
                cost_heap.decrease(edge.vertex, edge.weight)

    return total_cost

adj = read_graph()

# FIXME: remove after debugging
for source, row in enumerate(adj):
    print('DEBUG:', source, row)

start = int(input())
print(calculate_mst_weight(adj, start))
