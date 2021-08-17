#!/usr/bin/env python3

import bisect
import contextlib
import heapq


class KahnBacktracker:
    """Walks through topological sorts in lexicographic order."""

    __slots__ = ('_adj', '_indegs', '_roots', '_chain')

    def __init__(self, order, edges, chain):
        """Creates a backtracker for the specified graph."""
        if order < 0:
            raise ValueError("graph can't have negatively many vertices")
        if order == 0:
            raise ValueError("implementation doesn't accommodate empty graph")

        self._adj = [[] for _ in range(order + 1)]
        for src, dest in edges:
            self._adj[src].append(dest)

        self._indegs = [0] * (order + 1)
        self._roots = []

        self._chain = list(chain)
        if len(self._chain) != order:
            raise ValueError('initial state is not a topological sequence')

    def __iter__(self):
        """Returns the current object."""
        return self

    def __next__(self):
        """Advances to the next topological sequence."""
        # Retreat.
        while self._chain:
            src = self._chain.pop()

            for dest in self._adj[src]:
                # Increment indegrees of the forward neighbors of the old src.
                if not self._indegs[dest]:
                    # Remove dest from roots.
                    dest_index = bisect.bisect_left(self._roots, dest)
                    dest_root = self._roots.pop(dest_index)
                    assert dest == dest_root

                self._indegs[dest] += 1

            src_index = bisect.bisect_right(self._roots, src)

            with contextlib.suppress(IndexError):
                # Put the old src in roots and take the new src out.
                src, self._roots[src_index] = self._roots[src_index], src
                break

            self._roots.append(src)
        else:
            # No lexicographically next topological sort.
            raise StopIteration()

        self._chain.append(src)

        # Advance.
        while self._roots:
            # Decrement indegrees of the forward neighbors of the new src.
            for dest in self._adj[src]:
                self._indegs[dest] -= 1

                if not self._indegs[dest]:
                    # Add dest to roots.
                    heapq.heappush(self._roots, dest)

            # Extract the next src from roots.
            src = heapq.heappop(self._roots)
            self._chain.append(src)

        return self._chain[:]


def read_record():
    """Reads a line of input as a sequence of integers."""
    return map(int, input().split())


def print_record(values):
    """Prints a line of input from a sequnece of values."""
    print(' '.join(map(str, values)))


def run():
    """
    Reads a graph and a presumed-correct topological sorting of it. Emits the
    lexicographically next topological sorting of the graph, or -1 if none.
    """
    vertex_count, edge_count = read_record()
    edges = [tuple(read_record()) for _ in range(edge_count)]
    bt = KahnBacktracker(vertex_count, edges, read_record())
    try:
        print_record(next(bt))
    except StopIteration:
        print('-1')


if __name__ == '__main__':
    run()
