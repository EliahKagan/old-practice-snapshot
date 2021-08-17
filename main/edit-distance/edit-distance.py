class Solution:
    @staticmethod
    def minDistance(word1, word2):
        """
        Wagner-Fischer algorithm
        :type word1: str
        :type word2: str
        :rtype: int
        """
        nrows = 1 + len(word1)
        ncols = 1 + len(word2)
        dist = [[None for _j in range(ncols)] for _i in range(nrows)]

        for j in range(ncols):
            dist[0][j] = j

        for i in range(nrows):
            dist[i][0] = i

        for i, c1 in enumerate(word1):
            for j, c2 in enumerate(word2):
                if c1 == c2:
                    dist[i + 1][j + 1] = dist[i][j]
                else:
                    dist[i + 1][j + 1] = 1 + min(dist[i][j + 1], dist[i + 1][j],
                                                 dist[i][j])

        return dist[-1][-1]
