class Solution:
    def smallestStringWithSwaps(self, text: str,
                                pairs: List[List[int]]) -> str:
        """Sorts subsequences for each index component."""
        out = [None] * len(text)

        for indices in build_disjoint_sets(len(text), pairs).components():
            chars = sorted(text[i] for i in indices)
            for i, ch in zip(indices, chars):
                out[i] = ch

        return ''.join(out)


def build_disjoint_sets(vertex_count, edges):
    """Constructs a DisjointSets object for the specified graph."""
    sets = DisjointSets(vertex_count)

    for u, v in edges:
        sets.union(u, v)

    return sets


class DisjointSets:
    """Union-find data structure."""

    __slots__ = ('_elems',)

    def __init__(self, element_count):
        """Performs the specified number of makeset operations."""
        self._elems = [-1] * element_count

    def components(self):
        """Yields a sorted lists of elements for each disjoint set."""
        buckets = [[] for _ in range(len(self._elems))]

        for elem in range(len(self._elems)):
            buckets[self._find_set(elem)].append(elem)

        return (component for component in buckets if component)

    def union(self, elem1, elem2):
        """Unites the sets containing elem1 and elem2."""
        # Find the ancestors and stop if they are already the same.
        elem1 = self._find_set(elem1)
        elem2 = self._find_set(elem2)
        if elem1 == elem2:
            return

        # Union by rank.
        if self._elems[elem2] < self._elems[elem1]:
            # elem2 has higher (more negative) rank. It will be the parent.
            self._elems[elem1] = elem2
        else:
            if self._elems[elem1] == self._elems[elem2]:
                # elem1 and elem2 have the same rank. Promote elem1.
                self._elems[elem1] -= 1

            # elem1 has higher (more negative) rank. It will be the parent.
            self._elems[elem2] = elem1

    def _find_set(self, elem):
        """Finds the representative of the set with the specified element."""
        # Find the ancestor.
        leader = elem
        while self._elems[leader] >= 0:
            leader = self._elems[leader]

        # Compress the path.
        while elem != leader:
            self._elems[elem], elem = leader, self._elems[elem]

        return leader
