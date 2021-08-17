#!/usr/bin/env python3
"""Journey to the Moon (HackerRank) - by iterative DFS"""


def read_record():
    """Reads a line of input as a sequence of integers."""
    return map(int, input().split())


def read_graph():
    """Reads an undirected graph as an adjacency list."""
    vertex_count, edge_count = read_record()
    adj = [[] for _ in range(vertex_count)]

    for _ in range(edge_count):
        u, v = read_record()
        adj[u].append(v)
        adj[v].append(u)

    return adj


def component_sizes(adj):
    """Yields the size of each component of a graph from its adjacency list."""
    vis = [False] * len(adj)
    stack = []

    def measure(start):
        if vis[start]:
            return 0
        vis[start] = True
        stack.append(start)
        size = 1

        while stack:
            for neighbor in adj[stack.pop()]:
                if vis[neighbor]:
                    continue
                vis[neighbor] = True
                stack.append(neighbor)
                size += 1

        return size

    for start in range(len(adj)):
        size = measure(start)
        if size:
            yield size


def count_pairs(adj):
    """Computes the number of unordered vertex pairs in separate components."""
    sizes = list(component_sizes(adj))
    remaining = sum(sizes)

    total_pairs = 0
    for size in sizes:
        remaining -= size
        total_pairs += size * remaining

    return total_pairs


def run():
    """Reads an astronaut graph and reports the number of acceptable teams."""
    print(count_pairs(read_graph()))


if __name__ == '__main__':
    run()
