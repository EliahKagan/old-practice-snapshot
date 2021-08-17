from functools import reduce
from operator import xor

class Solution:
    def missingNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        # Compute n and take its two lowest-order bits.
        n = len(nums)
        phase = n % 4

        # Quickly compute the result of XORing 0 through n.
        if phase == 0:
            acc = n
        elif phase == 1:
            acc = 1
        elif phase == 2:
            acc = n + 1
        else:
            acc = 0

        # XOR that with each value we have to find the missing value.
        return reduce(xor, nums, acc)