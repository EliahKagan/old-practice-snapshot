class Solution:
    def majorityElement(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # Boyer-Moore
        count = 0
        for elem in nums:
            if count == 0:
                count = 1
                best = elem
            elif best == elem:
                count += 1
            else:
                count -= 1

        return best
