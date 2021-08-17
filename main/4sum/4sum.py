class Solution:
    def fourSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        ret = []

        n = len(nums)
        if n < 4:
            return ret

        nums.sort()
        gval = None

        for g in range(n - 3):
            if nums[g] == gval:
                continue

            gval = nums[g]
            hij_target = target - gval
            hval = None

            for h in range(g + 1, n - 2):
                if nums[h] == hval:
                    continue

                hval = nums[h]
                ij_target = hij_target - hval
                i = h + 1
                j = n - 1

                while i < j:
                    ival = nums[i]
                    jval = nums[j]
                    ij_sum = ival + jval

                    if ij_sum == ij_target:
                        ret.append((gval, hval, ival, jval))

                    if ij_sum <= ij_target:
                        while nums[i] == ival and i < j:
                            i += 1

                    if ij_sum >= ij_target:
                        while nums[j] == jval and i < j:
                            j -= 1

        return ret
