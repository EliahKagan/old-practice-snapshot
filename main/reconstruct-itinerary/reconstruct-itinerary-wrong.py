class AdjInfo:
    '''Indicates the destination of an edge and if it is visited.'''
    def __init__(self, dest):
        self.dest = dest
        self.visited = False

class Solution:
    def findItinerary(self, tickets):
        """
        :type tickets: List[List[str]]
        :rtype: List[str]
        """
        # Create the adjacency list.
        adj = collections.defaultdict(list)
        for src, dest in tickets:
            adj[src].append(AdjInfo(dest))

        # Sort each row lexicographically.
        for row in adj.values():
            row.sort(key=lambda info: info.dest)

        # We will use the target length and the current path in the search.
        length = len(tickets) + 1
        path = []

        # We will search in lexicographic order until a full path is found.
        def dfs(src):
            path.append(src)
            if len(path) == length:
                return path

            for info in adj[src]:
                if not info.visited:
                    info.visited = True

                    ret = dfs(info.dest)
                    if ret is not None:
                        return ret

                    info.visited = False

            return None

        return dfs('JFK')
