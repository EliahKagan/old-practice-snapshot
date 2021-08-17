class Solution:
    def findItinerary(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        # Create the adjacency list.
        adj = collections.defaultdict(list)
        for src, dest in tickets:
            adj[src].append(dest)

        # Sort each row so items can be popped in lexicographic order.
        for row in adj.values():
            row.sort(reverse=True)

        # We will build the path backwards.
        path = []

        # Recursive Hierholzer's algorithm.
        def dfs(src):
            row = adj[src]
            while row:
                dfs(row.pop())
            path.append(src)

        # Build the path and return it forwards.
        dfs('JFK')
        path.reverse()
        return path
