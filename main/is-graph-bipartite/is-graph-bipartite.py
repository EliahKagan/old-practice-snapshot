class Solution:
    def isBipartite(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: bool
        """
        vis = [0] * len(graph)
        
        def dfs(src, color):
            if vis[src] == color:
                return True
            
            if vis[src] == -color:
                return False
            
            assert vis[src] == 0
            vis[src] = color
            return all(dfs(dest, -color) for dest in graph[src])
        
        return all(dfs(start, 1) for start in range(len(graph))
                                 if vis[start] == 0)
