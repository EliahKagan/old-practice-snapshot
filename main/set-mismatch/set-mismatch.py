class Solution:
    def findErrorNums(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        counts = [0] * (len(nums) + 1)
        for i in nums:
            counts[i] += 1

        for i, c in enumerate(counts):
            if c != 1:
                if c == 0:
                    missing = i
                else:
                    repeated = i

        return [repeated, missing]
