''' Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above. '''

# Your task is to complete this function
# Function should return Topologically Sorted List
# Graph(graph) is a defaultict of type List
# n is no of edges
def topoSort(n, graph):
    vis = [False] * n
    out = []

    def dfs(v):
        if vis[v]:
            return
        vis[v] = True
        for w in graph[v]:
            dfs(w)
        out.append(v)

    for v in range(n):
        dfs(v)
    out.reverse()
    return out