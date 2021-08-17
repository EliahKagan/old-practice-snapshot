class Solution:
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) == 1:
            return nums[0]

        return max(self._rob_linear(nums[1:]), self._rob_linear(nums[:-1]))

    def _rob_linear(self, nums):
        far = near = 0
        for elem in nums:
            far, near = near, max(far + elem, near)
        return near
