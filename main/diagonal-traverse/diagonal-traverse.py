class Solution:
    def findDiagonalOrder(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        ret = []
        if not matrix or not matrix[0]:
            return ret

        m = len(matrix)
        n = len(matrix[0])
        i = 0
        j = 0

        while True:
            # travel up and right
            while 0 <= i and j < n:
                ret.append(matrix[i][j])
                i -= 1
                j += 1

            if j < n:  # above, and not also right of, the matrix
                i += 1
            else:  # right of the matrix
                i += 2
                j -= 1

            if i == m:
                break

            # travel down and left
            while i < m and 0 <= j:
                ret.append(matrix[i][j])
                i += 1
                j -= 1

            if i < m:  # left of, and not also below, the matrix
                j += 1
            else:  # below the matrix
                i -= 1
                j += 2

            if j == n:
                break

        return ret
