class Solution:
    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        ret = []
        if len(nums) < 3:
            return ret

        nums.sort()
        right_start = len(nums) - 1
        left_stop = right_start - 1

        left = 0
        while left != left_stop:
            left_elem = nums[left]
            mid = left + 1
            right = right_start

            while mid < right:
                mid_elem = nums[mid]
                right_elem = nums[right]
                total = left_elem + mid_elem + right_elem

                if total == 0:
                    ret.append([left_elem, mid_elem, right_elem])
                if total <= 0:
                    while mid < right and nums[mid] == mid_elem:
                        mid += 1
                if total >= 0:
                    while mid < right and nums[right] == right_elem:
                        right -= 1

            while left != left_stop and nums[left] == left_elem:
                left += 1

        return ret
