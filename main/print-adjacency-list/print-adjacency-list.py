#!/usr/bin/env python3

def read_record():
    return map(int, input().split())

for _ in range(int(input())):
    vertex_count, edge_count = read_record()
    adj = [[i] for i in range(vertex_count)]

    for _ in range(edge_count):
        u, v = read_record()
        adj[u].append(v)
        adj[v].append(u)

    for row in adj:
        print(*row, sep='-> ')
