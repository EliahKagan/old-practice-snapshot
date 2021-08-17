#!/usr/bin/env python3

import bisect
import contextlib
import heapq


class KahnBacktracker:
    """Walks through topological sorts in lexicographic order."""

    __slots__ = ('_adj', '_indegs', '_roots', '_chain')

    def __init__(self, order, edges, state):
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

        if len(chain) != order:
            raise ValueError('initial state is not a topological sequence')
        self._chain = chain[:]

    def __iter__(self):
        """Returns the current object."""
        return self

    def __next__(self):
        """Advances to the next topological sequence."""
        # REMEMBER: The tip of the chain may always be re-added as a root, but
        # doing so increments the indegrees of each of its forward neighbors,
        # and any that were zero before must be removed as roots.

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
            raise StopIteration()

        # Advance.
        while len(self._chain) != self._order:
            self._chain.append(src)

            # Decrement indegrees of the forward neighbors of the new src.
            for dest in self._adj[src]:
                self._indegs[dest] -= 1

                if not self._indegs[dest]:
                    # Add dest to roots.
                    heapq.heappush(self._roots, dest)

            src = heapq.heappop(self._roots)

        assert not self._roots
        return self._chain[:]

    @property
    def _order(self):
        """The number of vertices in the graph. This does not change."""
        return len(self._adj) - 1
