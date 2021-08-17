import collections
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


Frame = collections.namedtuple('Frame', ('vertex', 'neighbor'))
Frame.__doc__ = """A stack frame for iteratively implemented recursive DFS."""


def reverse_topological_sort(adj):
    """
    Computes a reverse topological sort of a directed graph via iteratively
    implemented recursive DFS, given the graph's adjacency list. Returns None
    if the graph is cyclic.
    """
    vis = [Color.WHITE] * len(adj)
    out = []
    stack = []

    def push(src):
        assert vis[src] is Color.WHITE, 'corrupted visitation list'
        vis[src] = Color.GRAY
        stack.append(Frame(src, iter(adj[src])))

    def has_cycle_from(start):
        if vis[start] is not Color.BLACK:
            push(start)

        while stack:
            vertex, neighbor = stack[-1]
            try:
                dest = next(neighbor)
            except StopIteration:
                vis[vertex] = Color.BLACK
                out.append(vertex)
                del stack[-1]
                continue

            if vis[dest] is Color.BLACK:
                continue
            if vis[dest] is Color.GRAY:
                return True
            push(dest)

        return False

    if any(has_cycle_from(start) for start in range(len(adj))):
        return None

    return out
