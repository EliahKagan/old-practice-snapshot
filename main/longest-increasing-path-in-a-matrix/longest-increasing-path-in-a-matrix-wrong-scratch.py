import contextlib
import functools
import itertools

def build_adjacency_list(matrix):
    m = len(matrix)
    n = len(matrix[0])
    adj = [[] for _ in range(m * n)]
    
    for i, j in itertools.product(range(m), range(n)):
        for h, k in ((i, j - 1), (i, j + 1), (i - 1, j), (i + 1, j)):
            with contextlib.suppress(IndexError):
                if matrix[i][j] < matrix[h][k]:
                    adj[i * n + j].append(h * n + k)
                    print("(%d, %d) -> (%d, %d)" % (i, j, h, k))
                    # Negative indices index from the end. FML.
    
    return adj

def max_path_length(adj):
    @functools.lru_cache(maxsize=None)
    def dfs(src):
        return 1 + max((dfs(dest) for dest in adj[src]), default=0)
    
    return max(dfs(start) for start in range(len(adj)))

class Solution:
    def longestIncreasingPath(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        if not matrix:
            return 0
        
        adj = build_adjacency_list(matrix)
        return max_path_length(adj)
