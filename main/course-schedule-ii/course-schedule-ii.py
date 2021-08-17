import enum


class Solution:
    @staticmethod
    def findOrder(numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        """Finds an order that courses may be taken. Returns [] on failure."""
        adj = build_graph(numCourses, prerequisites)
        out = reverse_topological_sort(adj)
        return [] if out is None else out


def build_graph(order, edges):
    """
    Builds an adjacency list for a directed graph with the given number of
    vertices (order) and directed edges u -> v represented (u, v).
    """
    adj = [[] for _ in range(order)]

    for src, dest in edges:
        adj[src].append(dest)

    return adj


@enum.unique
class Color(enum.Enum):
    """Visitation states for directed graph traversal."""
    WHITE = enum.auto()  # unvisited
    GRAY = enum.auto()   # visited but not yet fully explored
    BLACK = enum.auto()  # visited and fully explored


def reverse_topological_sort(adj):
    """
    Computes a reverse topological sort of a directed graph via recursive DFS,
    given the graph's adjacency list. Returns None if the graph is cyclic.
    """
    vis = [Color.WHITE] * len(adj)
    out = []

    def has_cycle_from(src):
        if vis[src] is Color.BLACK:
            return False
        if vis[src] is Color.GRAY:
            return True
        assert vis[src] is Color.WHITE, 'invalid vistation state'

        vis[src] = Color.GRAY
        if any(has_cycle_from(dest) for dest in adj[src]):
            return True
        vis[src] = Color.BLACK

        out.append(src)
        return False

    if any(has_cycle_from(start) for start in range(len(adj))):
        return None

    return out
