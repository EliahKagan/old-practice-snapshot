class Solution:
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        far = near = 0
        for elem in nums:
            far, near = near, max(far + elem, near)
        return near
