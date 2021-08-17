class Solution:
    @staticmethod
    def findOrder(numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        edges = ((src, dest) for dest, src in prerequisites)
        adj, indegs = build_adj_and_indegrees(numCourses, edges)
        
        res = checked_kahn_toposort(adj, indegs)
        if res is None:
            return []
        
        assert res == unchecked_dfs_toposort(adj)
        return res
    

def build_adj_and_indegrees(order, edges):
    """
    Creates an adjacency list and indegree counts from an order
    (vertex count) and edges.
    """
    adj = [[] for _ in range(order)]
    indegs = [0] * order
    
    for src, dest in edges:
        adj[src].append(dest)
        indegs[dest] += 1
    
    return adj, indegs


def checked_kahn_toposort(adj, indegs):
    """
    Topological sort by Kahn's algorithm with a stack. Mutates indegs.
    Returns None if the graph is cyclic.
    """
    out = []
    roots = zero_indices(indegs)
    
    while roots:
        src = roots.pop()
        out.append(src)
        
        for dest in adj[src]:
            indegs[dest] -= 1
            if not indegs[dest]:
                roots.append(dest)
    
    print(*out)
    return out if len(out) == len(adj) else None

    
def zero_indices(values):
    """Gets the indices of values that evaluate to false ("zeros")."""
    return [i for i, x in enumerate(values) if not x]
    

def unchecked_dfs_toposort(adj):
    """Topological sort by recursive DFS. Assumes the graph is acyclic."""
    vis = [False] * len(adj)
    out = []
    
    def dfs(src):
        if vis[src]:
            return
        vis[src] = True
        for dest in adj[src]:
            dfs(dest)
        out.append(src)
    
    for start in range(len(adj) - 1, -1, -1):
        dfs(start)
    
    out.reverse()
    print(*out)
    return out
