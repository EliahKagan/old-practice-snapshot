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

            if best_total < total:
                best_total = total
                best_left = left
                best_right = right

            if total < 0:
                total = 0
                left = right + 1

        # To just return the best_total, there's no need to keep track of left,
        # right, best_left, or best_right -- just right_elem and best_total.
        return best_total
