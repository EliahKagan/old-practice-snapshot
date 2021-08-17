#!/usr/bin/env python3
"""Dijkstra: Shortest Reach 2 (HackerRank problem)"""

import collections


class VertexCostPair:
    """A key-value pair where the key is a vertex and the value is a cost."""

    __slots__ = ('_vertex', 'cost')

    def __init__(self, vertex, cost):
        """Creates a pair for a vertex with a specified initial cost."""
        self._vertex = vertex
        self.cost = cost

    def __iter__(self):
        """Yields the vertex and cost values, to allow unpacking."""
        yield self._vertex
        yield self.cost

    @property
    def vertex(self):
        """Retrieves the vertex, which should never change."""
        return self._vertex


class PrimHeap:
    """A binary minheap suitable for Prim's and Dijkstra's algorithms."""

    __slots__ = ('_heap', '_map', '_len')

    def __init__(self, capacity):
        """Creates an empty PrimHeap with the specified maximum capacity."""
        self._heap = [None] * capacity  # index -> (vertex, cost)
        self._map = [None] * capacity   # vertex -> index
        self._len = 0

    def __len__(self):
        """The current size of the heap."""
        return self._len

    def __bool__(self):
        """True if nonempty, false if empty."""
        return self._len != 0

    def push_or_update(self, vertex, cost):
        """
        Decreases a vertex's cost to the specified value unless its cost is
        already lower. If the vertex doesn't exist, adds it with that cost.
        """
        child = self._map[vertex]

        if child is None:
            child = self._len
            self._len += 1
            item = VertexCostPair(vertex, cost)
        else:
            item = self._heap[child]
            if item.cost <= cost:
                return
            item.cost = cost

        self._sift_up(child, item)

    def pop(self):
        """
        Removes and returns the cheapest vertex and its cost from the heap.
        """
        assert self._len, "can't pop from an empty heap"

        result = self._heap[0]
        self._map[result.vertex] = None
        self._len -= 1

        if self._len:
            item = self._heap[self._len]
            self._heap[self._len] = None
            self._sift_down(0, item)
        else:
            self._heap[0] = None

        return result

    def _sift_up(self, child, item):
        """Sifts the specified item up from the specified child index."""
        while child:
            parent = (child - 1) // 2
            if self._heap[parent].cost <= item.cost:
                break
            self._heap[child] = self._heap[parent]
            self._map[self._heap[parent].vertex] = child
            child = parent

        self._heap[child] = item
        self._map[item.vertex] = child

    def _sift_down(self, parent, item):
        """Sifts the specified item down from the specified parent index."""
        while True:
            child = self._pick_child(parent)
            if child is None or item.cost <= self._heap[child].cost:
                break

            self._heap[parent] = self._heap[child]
            self._map[self._heap[child].vertex] = parent
            parent = child

        self._heap[parent] = item
        self._map[item.vertex] = parent

    def _pick_child(self, parent):
        """Picks index of the child that can switch places with the parent."""
        left = parent * 2 + 1
        if left >= self._len:
            return None

        right = left + 1
        if right != self._len:
            if self._heap[right].cost < self._heap[left].cost:
                return right

        return left


OutEdge = collections.namedtuple('OutEdge', ('dest', 'weight'))
OutEdge.__doc__ = """
    A weighted directed edge representation for an adjacency list.
    """


def read_value():
    """Reads a line of input as a single integer."""
    return int(input())


def read_record():
    """Reads a line of input as a sequences of integers."""
    return map(int, input().split())


def read_graph():
    """
    Reads a weighted edge-list representation of an undirected graph, emitting
    an adjacency list.
    """
    vertex_count, edge_count = read_record()
    adj = [[] for _ in range(vertex_count + 1)]  # +1 for 1-based indexing

    for _ in range(edge_count):
        first, second, weight = read_record()
        adj[first].append(OutEdge(second, weight))
        adj[second].append(OutEdge(first, weight))

    return adj


def dijkstra(adj, start):
    """
    Runs Dijkstra's algorithm on the graph represented by the adjacency list
    adj, from the specified start vertex. Returns costs, where costs[i] is the
    minimum edge weight sum from start to i, or None if there is no such path.
    """
    costs = [None] * len(adj)
    heap = PrimHeap(len(adj))
    heap.push_or_update(start, 0)

    while heap:
        src, src_cost = heap.pop()
        costs[src] = src_cost

        for dest, weight in adj[src]:
            if costs[dest] is None:
                heap.push_or_update(dest, src_cost + weight)

    return costs


def print_costs(costs, start):
    """
    Print costs of all but the unused zeroth vertex and the start vertex.
    Vertices that are unreachable have infinite cost, but we print -1 instead.
    """
    print(*((-1 if cost is None else cost)
            for cost in costs[1:start] + costs[(start + 1):]))


def run():
    """Reads input and solves as many test cases as requested."""
    for _ in range(read_value()):
        adj = read_graph()
        start = read_value()
        costs = dijkstra(adj, start)
        print_costs(costs, start)


if __name__ == '__main__':
    run()
