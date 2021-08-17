#!/usr/bin/env python3

"""
"Find the nearest clone" - Finds the shortest distance in a graph between any
pair of vertices of a specified color.
"""

import collections


State = collections.namedtuple('State', ('start', 'depth'))
State.__doc__ = """
    A visitation state for a vertex, tracking which root the traversal started
    from (start) and its distance from that root (depth).
"""


def read_value():
    """Reads a line as a single integer."""
    return int(input())


def read_record(length):
    """Reads a line as a sequence of integers."""
    ret = list(map(int, input().split()))
    if len(ret) != length:
        raise ValueError('wrong record length')
    return ret


def read_graph(vertex_count, edge_count):
    """Reads an undirected graph as an adjacency list."""
    adj = [[] for _ in range(vertex_count + 1)]

    for _ in range(edge_count):
        u, v = read_record(2)
        adj[u].append(v)
        adj[v].append(u)

    return adj


def read_roots(vertex_count):
    """
    Reads a sequence of vertex colors followed by the root color, and yields
    the vertices whose colorings indicate they are roots.
    """
    colors = read_record(vertex_count)
    root_color = read_value()
    return (vertex for vertex, color in enumerate(colors, 1)
            if color == root_color)


def read_roots_as_vis_and_queue(vertex_count):
    """
    Reads a sequence of vertex colors followed by the root color, and returns
    an initialized visitation list and queue populated with the root vertices.
    """
    vis = [None for _ in range(vertex_count + 1)]
    queue = collections.deque()

    for root in read_roots(vertex_count):
        vis[root] = State(root, 0)
        queue.append(root)

    return vis, queue


def multi_bfs(adj, vis, queue):
    """Finds the shortest distance between root by multidirectional BFS."""
    while queue:
        src = queue.popleft()

        for dest in adj[src]:
            if vis[dest] is None:
                vis[dest] = State(vis[src].start, vis[src].depth + 1)
                queue.append(dest)
            elif vis[dest].start != vis[src].start:
                return vis[src].depth + vis[dest].depth + 1

    return None


def run():
    """Solves the problem described by values read from standard input."""
    vertex_count, edge_count = read_record(2)
    adj = read_graph(vertex_count, edge_count)
    vis, queue = read_roots_as_vis_and_queue(vertex_count)
    result = multi_bfs(adj, vis, queue)
    print(-1 if result is None else result)


if __name__ == '__main__':
    run()
