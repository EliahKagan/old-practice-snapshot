class Solution:
    def topKFrequent(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: List[int]
        """
        freqs = collections.Counter(nums)
        return [e for e, _ in freqs.most_common(k)]
