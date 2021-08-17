class Solution:
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        best_total = -math.inf
        best_left = best_right = None

        total = 0
        left = 0
        for right, right_elem in enumerate(nums):
            total += right_elem
            if total < 0:
                total = 0
                left = right + 1
            elif best_total < total:
                best_total = total
                best_left = left
                best_right = right

        return best_total
