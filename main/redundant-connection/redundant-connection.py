class Element:
    def __init__(self, i):
        self.parent = i
        self.rank = 0

class Solution:
    def findRedundantConnection(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        n = len(edges)
        elems = [Element(i) for i in range(n + 1)]

        def findSet(i):
            # find the root
            j = i
            while j != elems[j].parent:
                j = elems[j].parent

            # compress the path
            while i != j:
                p = elems[i].parent
                elems[i].parent = j
                i = p

            return j

        def union(i, j): # returns True iff they were separate
            i = findSet(i)
            j = findSet(j)
            if i == j:
                return False

            if elems[i].rank < elems[j].rank:
                elems[i].parent = j
            else:
                if elems[i].rank == elems[j].rank:
                    elems[i].rank += 1
                elems[j].parent = i

            return True

        for edge in edges:
            if not union(*edge):
                return edge

        raise ValueError('no redundant edge found')