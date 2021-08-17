#!/usr/bin/env python3

import bisect
import contextlib


class KahnBacktracker:
    """Walks through topological sorts in lexicographic order."""

    __slots__ = ('_adj', '_indegs', '_roots', '_chain', '_advancing')

    def __init__(self, order, edges, state):
        """Creates a backtracker for the specified graph."""
        if order < 0:
            raise ValueError("graph can't have negatively many vertices")
        if order == 0:
            raise ValueError("implementation doesn't accommodate empty graph")
        self._adj = [[] for _ in range(order + 1)]
        self._indegs = [0] * (order + 1)

        for src, dest in edges:
            self._adj[src].append(dest)
            # self._indegrees[dest] += 1  # FIXME: remove this entirely?

        # TODO: Test if sorting the rows would make backtracking faster.

        self._roots = []
        if len(chain) != order:
            raise ValueError('initial state is not a topological sequence')
        self._chain = chain[:]
        self._advancing = False

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
            old = self._chain.pop()
            for dest in self._adj[old]:
                if not self._indegs[dest]:

                    # self._roots.remove(dest)  # do this faster
                self._indegs[dest] += 1

            #####
            index = bisect.bisect_right(self._roots, old)

            if index != len(self._roots):

                new = self._roots[index]
                self._roots[index] = old

            if index == len(self._roots):
                self._roots.append(old)

            with contextlib.suppress(IndexError):
                old = self._chain.pop()
                index =

                bisect.insort_right(self._roots, old)
                index = bisect.bisect_right(self._roots, old)



    def next_SCRATCHWORK(self): # FIXME: delete
        while not (len(self._chain) == self._order and self._advancing):
            if self._advancing:
                self._advance()
            else:
                self._retreat()

        self._advancing = False
        return self._chain[:]

    @property
    def _order(self):
        """The number of vertices in the graph. This does not change."""
        return len(self._adj) - 1

    def _retreat(self):
        """Retreat until """
