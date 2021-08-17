import collections


class Solution:
    @staticmethod
    def findOrder(numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        """Finds an order that courses may be taken. Returns [] on failure."""
        graph = Graph(numCourses, ((src, dest) for dest, src in prerequisites))
        result = graph.topological_sort()
        return [] if result is None else result


class Graph:
    """A directed graph supporting topological sorting."""

    __slots__ = ('_adj', '_indegrees', '_sort_started')

    def __init__(self, vertex_count, edges):
        """Creates a directed graph of the specified vertex count and edges."""
        self._adj = [[] for _ in range(vertex_count)]
        self._indegrees = [0] * vertex_count
        self._sort_started = False

        for src, dest in edges:
            self._adj[src].append(dest)
            self._indegrees[dest] += 1

    def topological_sort(self):
        """
        Yields topologically sorted vertices via Kahn's algorithm with BFS,
        or None if the graph is cyclic. Call at most once per Graph object.
        """
        if self._sort_started:
            raise ValueError('toplogical_sort already called')
        self._sort_started = True

        out = []

        roots = self._roots()
        while roots:
            src = roots.popleft()
            out.append(src)

            for dest in self._adj[src]:
                self._indegrees[dest] -= 1
                if self._indegrees[dest] == 0:
                    roots.append(dest)

        return out if len(out) == len(self._adj) else None

    def _roots(self):
        """Obtains a deque of the root vertices."""
        return collections.deque(src for src, indegree
                                 in enumerate(self._indegrees)
                                 if indegree == 0)
