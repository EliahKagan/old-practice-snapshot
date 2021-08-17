class Solution:
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        high = low = 0
        for elem in nums:
            high, low = (high & ~elem) | (low & elem), \
                        ~high & (low ^ elem)

        if high:
            raise ValueError('unmet precondition or bug')
        return low
