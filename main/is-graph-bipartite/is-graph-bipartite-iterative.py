class Solution:
    def isBipartite(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: bool
        """
        vis = [0] * len(graph)
        
        def dfs(start):
            stack = [(start, 1)]
            
            while stack:
                src, color = stack.pop()
                
                if vis[src] == color:
                    continue
                
                if vis[src] == -color:
                    return False
                
                assert vis[src] == 0
                vis[src] = color
                stack.extend((dest, -color) for dest in graph[src])
            
            return True
        
        return all(dfs(start) for start in range(len(graph))
                              if vis[start] == 0)
