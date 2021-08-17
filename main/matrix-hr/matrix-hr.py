#!/usr/bin/env python3

"""
"Matrix" graph theory problem from HackerRank - union-find solution.
"""

import collections


class DisjointSets:
    """
    Disjoint-set-union data structure where each component is inactive
    (uninfected) or active (infected). The union of components is active when
    either was already active. The purpose of this data structure is to detect
    each time two already-active components are united.
    """

    __slots__ = ('_parents', '_ranks', '_active')

    def __init__(self, count):
        """Makes the specified number of singletons."""
        if count < 0:
            raise ValueError('negative count makes no sense')

        self._parents = list(range(count))
        self._ranks = [0] * count
        self._active = [False] * count

    def activate(self, vertex):
        """Marks the specified element as an active vertex."""
        self._check_exists(vertex)
        self._active[vertex] = True

    def union(self, vertex1, vertex2):
        """Unite by rank. Returns true iff separate active sets were joined."""
        self._check_exists(vertex1)
        self._check_exists(vertex2)

        # Find the ancestors and stop if they are already the same.
        vertex1 = self._find_set(vertex1)
        vertex2 = self._find_set(vertex2)
        if vertex1 == vertex2:
            return False

        # Unite by rank.
        if self._ranks[vertex1] < self._ranks[vertex2]:
            return self._join(vertex2, vertex1)
        if self._ranks[vertex1] == self._ranks[vertex2]:
            self._ranks[vertex1] += 1
        return self._join(vertex1, vertex2)

    def _find_set(self, vertex):
        """Finds the representative element, doing full path compression."""
        # Find the ancestor.
        leader = vertex
        while leader != self._parents[leader]:
            leader = self._parents[leader]

        # Compress the path.
        while vertex != leader:
            self._parents[vertex], vertex = leader, self._parents[vertex]

        return leader

    def _join(self, parent, child):
        """Joins the child to the parent. Returns true iff both were active."""
        self._parents[child] = parent

        if self._active[child]:
            if self._active[parent]:
                return True
            self._active[parent] = True

        return False

    def _check_exists(self, vertex):
        """Raises an exception if the vertex does not exist."""
        if not 0 <= vertex < len(self._parents):
            raise IndexError('vertex does not exist (out of range)')


Edge = collections.namedtuple('Edge', ('vertex1', 'vertex2', 'weight'))
Edge.__doc__ = """An edge in a weighted undirected graph."""


def read_value():
    """Reads a line of input as a single integer."""
    return int(input())


def read_record():
    """Reads a line of input as a sequence of integers."""
    return map(int, input().split())


def read_edges_sorted(edge_count):
    """Reads and reverse-weight sorts the specified number of edges."""
    edges = [Edge._make(read_record()) for _ in range(edge_count)]
    edges.sort(key=lambda edge: edge.weight, reverse=True)
    return edges


def read_vertices(count, active_count):
    """Reads one active vertex per line. Makes singletons for all vertices."""
    sets = DisjointSets(count)
    for _ in range(active_count):
        sets.activate(read_value())
    return sets


def run():
    """Solves the problem as described on standard input."""
    city_count, machine_count = read_record()
    if city_count <= 0:
        raise ValueError('must have at least one city')
    if machine_count < 0:
        raise ValueError("can't have negatively many machines")
    if city_count < machine_count:
        raise ValueError("can't have more machines than cities")

    edges = read_edges_sorted(city_count - 1)
    sets = read_vertices(city_count, machine_count)
    total_bridge_weight = 0
    bridge_count = 0  # for error checking and debugging

    for vertex1, vertex2, weight in edges:
        if sets.union(vertex1, vertex2):
            total_bridge_weight += weight
            bridge_count += 1

    assert bridge_count == machine_count - 1
    print(total_bridge_weight)


if __name__ == '__main__':
    run()
