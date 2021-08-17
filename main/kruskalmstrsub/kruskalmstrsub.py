#!/usr/bin/env python3

from collections import namedtuple

class DisjointSets(object):
    def __init__(self, count):
        '''Creates count non-overlapping sets, each containing one element.'''
        self._elems = [-1] * count

    def union(self, i, j):
        '''Joins the set containing i with the set containing j. Returns False
        if they were already in the same set. Returns True if they were not.'''
        # Find the ancestors and check if they're already the same.
        i = self._find(i)
        j = self._find(j)
        if i == j:
            return False

        # Unite the sets by rank.
        if self._elems[i] > self._elems[j]:
            self._elems[i] = j  # j has superior (more negative) rank
        else:
            if self._elems[i] == self._elems[j]:
                self._elems[i] -= 1  # i and j have equal rank, so promote i

            self._elems[j] = i  # i has superior (more negative rank)

        return True

    def _find(self, i):
        '''Finds the representative element for the set that contains i.'''
        # Find the ancestor.
        j = i
        while self._elems[j] >= 0:
            j = self._elems[j]

        # Compress the path.
        while i != j:
            self._elems[i], i = j, self._elems[i]

        return j

Edge = namedtuple('Edge', ('x', 'y', 'r'))

def read_record():
    return map(int, input().split())

v, e = read_record()
edges = [Edge(*read_record()) for _ in range(e)]
edges.sort(key=lambda edge: (edge.r, edge.x + edge.y))

sets = DisjointSets(v + 1)  # because we're not using 0
print(sum(edge.r for edge in edges if sets.union(edge.x, edge.y)))
