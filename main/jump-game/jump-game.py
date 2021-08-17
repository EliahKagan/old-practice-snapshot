class Solution:
    def canJump(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        j = len(nums) - 1
        while j != 0:
            for i in range(j - 1, -2, -1):
                if i + nums[i] >= j:
                    break
            if i == -1:
                return False
            j = i

        return True
