class Solution:
    def majorityElement(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        length = len(nums)
        half = length // 2
        while True:
            best = nums[random.randrange(length)]
            count = 0
            for elem in nums:
                if best == elem:
                    count += 1
                    if count > half:
                        return best
