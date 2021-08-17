#!/usr/bin/env python3

SHOW_ADJACENCY_LIST = False

def read_record():
    return map(int, input().split())

vertex_count, edge_count = read_record()
connections = list(read_record())

if len(connections) != edge_count * 2:
    raise ValueError('wrong record length')

adj = [[] for _ in range(vertex_count)]

def add_edge(u, v):
    adj[u].append(v)
    adj[v].append(u)

for i in range(0, len(connections), 2):
    add_edge(connections[i], connections[i + 1])

if SHOW_ADJACENCY_LIST:
    print('Adjacency list:')
    print(adj)
    print()

visited = [False] * vertex_count

def dfs(out, u):
    if not visited[u]:
        visited[u] = True
        out.append(u)
        for v in adj[u]:
            dfs(out, v)

components = []

for u in range(vertex_count):
    cur = []
    dfs(cur, u)
    if cur:
        cur.sort()
        components.append(cur)

print('Components:')
for component in components:
    print(component)

print('\nThat was', len(components), 'component(s), with sizes:',
        ', '.join(str(len(component)) for component in components))
