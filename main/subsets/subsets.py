class Solution:
    def subsets(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        def make_subset(bits):
            for val in nums:
                if bits & 1:
                    yield val
                bits >>= 1

        def make_all_subsets():
            for bits in range(2**len(nums)):
                yield list(make_subset(bits))

        return list(make_all_subsets())
