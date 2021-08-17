#!/usr/bin/env python3
"""Roads and Libraries (HackerRank) - by union-find"""


class DisjointSets:
    """Disjoint-set-union data structure."""

    __slots__ = ('_parents', '_ranks')

    def __init__(self, element_count):
        """Performs the specified number of makeset operations."""
        self._parents = list(range(element_count))
        self._ranks = [0] * element_count

    def union(self, elem1, elem2):
        """
        Unites the sets containing the specified elements.
        Returns True if they were originally separate sets, False otherwise.
        """
        # Find the ancestors and stop if they are already the same.
        elem1 = self._find_set(elem1)
        elem2 = self._find_set(elem2)
        if elem1 == elem2:
            return False

        # Union by rank.
        if self._ranks[elem1] < self._ranks[elem2]:
            self._parents[elem1] = elem2
        else:
            if self._ranks[elem1] == self._ranks[elem2]:
                self._ranks[elem1] += 1
            self._parents[elem2] = elem1

        return True

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


def read_value():
    """Reads a line of input as a single integer."""
    return int(input())


def read_record():
    """Reads a line of input as a sequence of integers."""
    return map(int, input().split())


def run():
    """Reads city/road graphs. Computes the cost to restore library access."""
    for _ in range(read_value()):
        city_count, road_count, library_cost, road_cost = read_record()
        if road_cost < library_cost:
            sets = DisjointSets(city_count + 1)  # +1 for 1-based indexing
            new_road_count = sum(sets.union(*read_record())
                                 for _ in range(road_count))
            component_count = city_count - new_road_count
            print(component_count * library_cost + new_road_count * road_cost)
        else:
            for _ in range(road_count):
                input()  # consume and discard edge information
            print(city_count * library_cost)


if __name__ == '__main__':
    run()
