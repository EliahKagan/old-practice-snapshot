import enum

class Solution:
    def canFinish(self, numCourses, prerequisites):
        """
        :type numCourses: int
        :type prerequisites: List[List[int]]
        :rtype: bool
        """
        if numCourses < 0:
            raise ValueError("can't have negatively many courses")

        adj = Solution._buildAdjacencyList(numCourses, prerequisites)
        return not Solution._hasCycle(adj)

    @staticmethod
    def _buildAdjacencyList(numCourses, prerequisites):
        adj = [[] for _ in range(numCourses)]

        for dest, src in prerequisites:
            adj[src].append(dest)

        return adj

    @staticmethod
    def _hasCycle(adj):
        vis = [Solution._Color.WHITE] * len(adj)

        def dfs(src):
            if vis[src] is Solution._Color.WHITE:
                vis[src] = Solution._Color.GRAY
                if any(dfs(dest) for dest in adj[src]):
                    return True
                vis[src] = Solution._Color.BLACK
                return False
            elif vis[src] is Solution._Color.GRAY:
                return True
            elif vis[src] is Solution._Color.BLACK:
                return False
            else:
                raise AssertionError('invalid visitation state')

        return any(dfs(src) for src in range(len(vis)))

    @enum.unique
    class _Color(enum.Enum):
        WHITE = 0
        GRAY = 1
        BLACK = 2
