#!/usr/bin/env python3

"""
"Components in a graph" HackerRank problem.
"""

import math


class DisjointSets:
    """Disjoint-set-union data structure that can enumerate component sizes."""

    __slots__ = ('_parents', '_sizes')

    def __init__(self, count):
        """Performs the specified number of makeset operations."""
        self._parents = list(range(count))
        self._sizes = [1] * count

    def sizes(self):
        """Yields the sizes of each component."""
        return (self._sizes[elem]
                for elem in range(len(self._parents))
                if elem == self._parents[elem])

    def union(self, elem1, elem2):
        """Unites the sets containing the specified elements."""
        if not (self._exists(elem1) and self._exists(elem2)):
            raise IndexError('attempted union with nonexistent element')

        # Find the ancestors and stop if they are already the same.
        elem1 = self._find_set(elem1)
        elem2 = self._find_set(elem2)
        if elem1 == elem2:
            return

        # Unite the sets by size.
        if self._sizes[elem1] < self._sizes[elem2]:
            self._join(elem2, elem1)
        else:
            self._join(elem1, elem2)

    def _find_set(self, elem):
        """Finds the representative of the set containing elem."""
        # Find the ancestor.
        leader = elem
        while leader != self._parents[leader]:
            leader = self._parents[leader]

        # Fully compress the path.
        while elem != leader:
            self._parents[elem], elem = leader, self._parents[elem]

        return leader

    def _join(self, parent, child):
        """Joins the child to the parent."""
        self._sizes[parent] += self._sizes[child]
        self._parents[child] = parent

    def _exists(self, elem):
        """Checks if the specified element is a member of any set."""
        return 0 <= elem < len(self._parents)


def read_value():
    """Reads a line of input as a single integer."""
    return int(input())


def read_record():
    """Reads a line of input as a sequence of integers."""
    return map(int, input().split())


def min_max_nonsingleton_sizes(sets):
    """Finds the minimum and maximum nonsingleton set sizes."""
    low = math.inf
    high = -math.inf

    for size in sets.sizes():
        if size > 1:
            low = min(low, size)
            high = max(high, size)

    return low, high


def run():
    """Reads a graph. Reports min and max sizes of non-singleton components."""
    n = read_value()
    sets = DisjointSets(n * 2 + 1)  # +1 for 1-based indexing

    for _ in range(n):
        sets.union(*read_record())

    print(*min_max_nonsingleton_sizes(sets))


if __name__ == '__main__':
    run()
