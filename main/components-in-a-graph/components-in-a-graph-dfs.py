#!/usr/bin/env python3

"""
"Components in a graph" HackerRank problem - DFS solution.
"""

import math


def read_value():
    """Reads a line of input as a single integer."""
    return int(input())


def read_record():
    """Reads a line of input as a sequence of integers."""
    return map(int, input().split())


def read_graph():
    """Reads N edges and builds an undirected graph with 2N vertices."""
    n = read_value()
    adj = [[] for _ in range(n * 2 + 1)]  # +1 for 1-based indexing

    for _ in range(n):
        u, v = read_record()
        adj[u].append(v)
        adj[v].append(u)

    return adj


def nonsingelton_component_sizes(adj):
    """Yields sizes of each graph component with more than one vertex."""
    vis = [False] * len(adj)

    def measure(src):
        if vis[src]:
            return 0
        vis[src] = True
        return 1 + sum(measure(dest) for dest in adj[src])

    for src in range(len(adj)):
        size = measure(src)
        if size > 1:
            yield size


def run():
    """Reads a graph. Reports min and max sizes of non-singleton components."""
    low = math.inf
    high = -math.inf

    for size in nonsingelton_component_sizes(read_graph()):
        low = min(low, size)
        high = max(high, size)

    print(low, high)


if __name__ == '__main__':
    run()
