class Solution:
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        ret = []
        nums.sort()
        last = len(nums) - 1

        for center in range(1, last):
            compl = -nums[center]
            left = 0
            right = last

            while True:
                partial = nums[left] + nums[right]
                if partial < compl:     # shrink the window from the left
                    left += 1
                    if left == center:
                        break
                elif partial != compl:  # shrink the window from the right
                    right -= 1
                    if right == center:
                        break
                else: # record the match and shrink the window from both sides
                    ret.append([nums[left], -compl, nums[right]])
                    left += 1
                    if left == center:
                        break
                    right -= 1
                    if right == center:
                        break

        return ret
