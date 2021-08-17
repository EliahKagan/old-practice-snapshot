#!/usr/bin/env python3

import heapq

class DisjointSets:
    def __init__(self, size):
        self._parents = list(range(size))
        self._ranks = [0] * size

    def union(self, i, j):
        '''Unites the sets of i and j. Returns true iff they were separate.'''
        # find the ancestors and stop if they are already the same
        i = self._find(i)
        j = self._find(j)
        if i == j:
            return False

        # unite by rank
        if self._ranks[i] < self._ranks[j]:
            self._parents[i] = j
        else:
            if self._ranks[i] == self._ranks[j]:
                self._ranks[i] += 1
            self._parents[j] = i

        return True

    def _find(self, i):
        # find the ancestor
        j = i
        while j != self._parents[j]:
            j = self._parents[j]

        # compress the path
        while i != j:
            self._parents[i], i = j, self._parents[i]

        return j

class Edge:
    def __init__(self, u, v, wt):
        self.u = u
        self.v = v
        self.wt = wt

    def __lt__(self, other):
        return self.wt < other.wt

    def __gt__(self, other):
        return self.wt > other.wt

def read_record():
    return map(int, input().split())

def read_edges(edge_count):
    return [Edge(*read_record()) for _ in range(edge_count)]

def compute_mst_weight(vertex_count, edges):
    '''Calculates the total weight of an MST. (Mutates the edges parameter.)'''
    if vertex_count < 2:
        return 0

    # Add 1 because we are not using vertex 0 (we want 1-based indexing).
    sets = DisjointSets(vertex_count + 1)

    # This may save time because we only pop edges until we have an MST.
    heapq.heapify(edges)

    # Pick edges until we have an MST or all edges were considered.
    weight = 0
    needed = vertex_count - 1
    while needed and edges:
        edge = heapq.heappop(edges)
        if sets.union(edge.u, edge.v):
            weight += edge.wt
            needed -= 1

    return weight

vertex_count, edge_count = read_record()
print(compute_mst_weight(vertex_count, read_edges(edge_count)))
