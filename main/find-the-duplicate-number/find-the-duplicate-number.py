class Solution:
    def findDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # find where tortoise and hare indices meet
        i = j = 0
        while True:
            i = nums[i]
            j = nums[nums[j]]
            if i == j:
                break

        # find where the cycle begins
        i = 0
        while i != j:
            i = nums[i]
            j = nums[j]

        return i
