#!/usr/bin/env python3

import collections

EDGE_LENGTH = 6
NO_PATH = -1

def read_value():
    return int(input())

def read_record():
    return map(int, input().split())

def read_graph():
    vertex_count, edge_count = read_record()
    adj = [[] for _ in range(vertex_count + 1)] # +1 for 1-base indexing

    for _ in range(edge_count):
        u, v = read_record()
        adj[u].append(v)
        adj[v].append(u)

    return adj

def bfs(adj, start):
    costs = [None] * len(adj)

    queue = collections.deque((start,))
    level = 0

    while queue:
        for _ in range(len(queue)):
            src = queue.popleft()
            if costs[src] is None:
                costs[src] = level
                queue.extend(adj[src])

        level += 1

    return costs

def print_costs(costs, start):
    print(*(NO_PATH if cost is None else cost * EDGE_LENGTH
            for cost in costs[1:start] + costs[(start + 1):]))

for _ in range(read_value()):
    adj = read_graph()
    start = read_value()
    costs = bfs(adj, start)
    print_costs(costs, start)
