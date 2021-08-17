class Solution:
    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if len(nums) < 3:
            return max(nums) if nums else 0

        nums[2] += nums[0]
        for i in range(3, len(nums)):
            nums[i] += max(nums[i - 2], nums[i - 3])

        return max(nums[-1], nums[-2])
