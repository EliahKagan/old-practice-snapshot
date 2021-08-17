class Solution:
    def searchRange(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        left = bisect.bisect_left(nums, target)
        right = bisect.bisect_right(nums, target, left)
        return (-1, -1) if left == right else (left, right - 1)
