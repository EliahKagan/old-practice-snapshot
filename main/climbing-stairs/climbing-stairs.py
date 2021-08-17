table = [1, 1]

class Solution:
    def climbStairs(self, n):
        """
        :type n: int
        :rtype: int
        """
        for _ in range(len(table), n + 1):
            table.append(table[-1] + table[-2])

        return table[n]
