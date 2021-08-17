#!/usr/bin/env python3

from collections import defaultdict

class DisjointSets(object):
    def __init__(self, count):
        '''Creates count non-overlapping sets, each containing one element.'''
        self._elems = [-1] * count

    def __iter__(self):
        '''Yields each disjoint set as a list of values.'''
        components = defaultdict(list)
        for i in range(len(self._elems)):
            components[self._find(i)].append(i)

        for key in sorted(components):
            yield components[key]

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

def read_record():
    return map(int, input().split())

vertex_count, edge_count = read_record()
connections = list(read_record())

if len(connections) != edge_count * 2:
    raise ValueError('wrong record length')

sets = DisjointSets(vertex_count)
for i in range(0, len(connections), 2):
    sets.union(connections[i], connections[i + 1])

components = sorted(sets) # iterate and convert to sorted list

print('Components:')
for component in components:
    print(component)

print('\nThat was', len(components), 'component(s), with sizes:',
        ', '.join(str(len(component)) for component in components))
