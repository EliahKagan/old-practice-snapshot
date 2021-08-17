#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

def read_graph(vertex_count, edge_count):
    adj = [[] for _ in range(vertex_count)]

    it = read_record()
    for _ in range(edge_count):
        src = next(it)
        dest = next(it)
        adj[src].append(dest)

    return adj

def reflect_graph(adj):
    for row in adj:
        row.reverse()

for _ in range(int(input())):
    vertex_count, edge_count = read_record()
    vertex_count += 1 # because we're ignoring vertex 0, for 1-based indexing
    a = read_graph(vertex_count, edge_count)
    b = read_graph(vertex_count, edge_count)
    reflect_graph(b)
    print(1 if a == b else 0)
