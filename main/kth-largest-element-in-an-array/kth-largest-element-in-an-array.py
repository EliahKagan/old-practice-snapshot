class Solution:
    def findKthLargest(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        # I could use quickselect, but Timsort is really fast...
        nums.sort()
        return nums[-k]
