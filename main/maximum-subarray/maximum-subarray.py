class Solution:
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        best_total = -math.inf

        total = 0
        for x in nums:
            total += x
            if best_total < total:
                best_total = total
            if total < 0:
                total = 0

        return best_total
