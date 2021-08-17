class Solution:
    @staticmethod
    def sortArrayByParity(a):
        """
        :type A: List[int]
        :rtype: List[int]
        """
        a.sort(key=lambda x: x % 2)
        return a
