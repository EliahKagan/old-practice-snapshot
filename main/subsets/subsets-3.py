class Solution:
    def subsets(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def subsetsTo(stop):
            if stop == 0:
                yield []
                return

            singleton = [nums[stop - 1]]
            for subset in subsetsTo(stop - 1):
                yield subset
                yield subset + singleton

        return list(subsetsTo(len(nums)))