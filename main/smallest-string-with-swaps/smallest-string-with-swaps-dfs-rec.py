class Solution:
    def smallestStringWithSwaps(self, text: str,
                                pairs: List[List[int]]) -> str:
        """Sorts subsequences for each index component."""
        out = [None] * len(text)

        for indices in components(build_graph(len(text), pairs)):
            chars = sorted(text[i] for i in indices)
            for i, ch in zip(indices, chars):
                out[i] = ch

        return ''.join(out)


def build_graph(order: int, edges: List[List[int]]) -> List[List[int]]:
    """Builds an adjacency list from the edges of an undirected graph."""
    adj = [[] for _ in range(order)]

    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)

    return adj


def components(adj: List[List[int]]):
    """Yields sorted components of a graph. Finds them via recursive DFS."""
    vis = [False] * len(adj)

    def dfs(src):
        if vis[src]:
            return
        vis[src] = True
        yield src
        for dest in adj[src]:
            yield from dfs(dest)

    return (sorted(dfs(start)) for start in range(len(adj)) if not vis[start])
