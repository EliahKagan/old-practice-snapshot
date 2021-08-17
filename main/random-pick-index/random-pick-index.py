class Solution:
    def __init__(self, nums):
        """
        :type nums: List[int]
        """
        self._bins = collections.defaultdict(list)
        
        for i, e in enumerate(nums):
            self._bins[e].append(i)

    def pick(self, target):
        """
        :type target: int
        :rtype: int
        """
        return random.choice(self._bins[target])


# Your Solution object will be instantiated and called as such:
# obj = Solution(nums)
# param_1 = obj.pick(target)
