''' Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above. '''

import collections

def get_initial_indegrees(adj):
    indegrees = [0] * len(adj)
    
    for row in adj:
        for dest in row:
            indegrees[dest] += 1
    
    return indegrees

def get_roots(indegrees):
    return collections.deque(dest for dest, indeg
                                  in enumerate(indegrees)
                                  if not indeg)

# Your task is to complete this function
# Function should return Topologically Sorted List
# Graph(graph) is a defaultict of type List
# n is no of edges
def topoSort(n, graph):
    adj = [graph[v] for v in range(n)]
    indegrees = get_initial_indegrees(adj)
    roots = get_roots(indegrees)
    ret = []
    
    while roots:
        src = roots.popleft()
        ret.append(src)
        
        for dest in adj[src]:
            assert indegrees[dest] > 0
            indegrees[dest] -= 1
            if not indegrees[dest]:
                roots.append(dest)
    
    return ret
