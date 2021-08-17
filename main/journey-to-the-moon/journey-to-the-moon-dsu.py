#!/usr/bin/env python3
"""Journey to the Moon (HackerRank) - by union-find"""


class DisjointSets:
    """Disjoint-set-union data structure with component-size tracking."""

    __slots__ = ('_parents', '_sizes')

    def __init__(self, element_count):
        """Performs the specified number of makeset operations."""
        self._parents = list(range(element_count))
        self._sizes = [1] * element_count

    def sizes(self):
        """Yields the size of each set."""
        return (self._sizes[elem]
                for elem, parent in enumerate(self._parents)
                if elem == parent)

    def union(self, elem1, elem2):
        """Unites the sets containing the specified elements."""
        # Find the ancestors and stop if they are already the same.
        elem1 = self._find_set(elem1)
        elem2 = self._find_set(elem2)
        if elem1 == elem2:
            return

        # Union by size.
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

        # Compress the path.
        while elem != leader:
            self._parents[elem], elem = leader, self._parents[elem]

        return leader

    def _join(self, parent, child):
        """Joins the child to the parent."""
        self._sizes[parent] += self._sizes[child]
        self._parents[child] = parent


def count_pairs(sets):
    """Computes the number of unordered elelemt pairs in disjoint sets."""
    total_size = total_pairs = 0

    for size in sets.sizes():
        total_pairs += total_size * size
        total_size += size

    return total_pairs


def read_record():
    """Reads a line of input as a sequence of integers."""
    return map(int, input().split())


def run():
    """Reads an astronaut graph and reports the number of acceptable teams."""
    vertex_count, edge_count = read_record()

    sets = DisjointSets(vertex_count)
    for _ in range(edge_count):
        sets.union(*read_record())

    print(count_pairs(sets))


if __name__ == '__main__':
    run()
