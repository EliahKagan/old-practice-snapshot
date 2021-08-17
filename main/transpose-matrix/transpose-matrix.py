class Solution:
    @staticmethod
    def transpose(A):
        """
        :type A: List[List[int]]
        :rtype: List[List[int]]
        """
        return tuple(zip(*A))
