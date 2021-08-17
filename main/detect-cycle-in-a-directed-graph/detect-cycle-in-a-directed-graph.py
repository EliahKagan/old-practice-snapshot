'''Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.'''

from enum import Enum

# Your task is to complete this function
# Function should return True/False or 1/0
# Graph(graph) is a defaultict of type List
# n is no of Vertices
def isCyclic(n, graph):
    Color = Enum('Color', 'WHITE GRAY BLACK')
    vis = [Color.WHITE] * n

    def isCyclicFrom(u):
        if vis[u] is Color.WHITE:
            vis[u] = Color.GRAY
            if any(isCyclicFrom(v) for v in graph[u]):
                return True
            vis[u] = Color.BLACK
        elif vis[u] is Color.GRAY:
            return True
        elif vis[u] is Color.BLACK:
            return False
        else:
            raise AssertionError('internal error: invalid visitation state')

    return any(isCyclicFrom(u) for u in range(n))
