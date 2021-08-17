from functools import reduce
from operator import xor

class Solution:
    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        # Call the two values we seek a and b. XOR together all the values so
        # the others, which are paired, drop out, and we get a XOR b.
        a_xor_b = reduce(xor, nums)
        if not a_xor_b:
            raise ValueError("input doesn't have 2 unique values")

        # Find a bit that is set in one of a and b but not the other.
        bit = 1
        while not a_xor_b & bit:
            bit <<= 1

        # XOR together just the values with that bit set, to get either a or b.
        # Without loss of generality, call this a.
        a = reduce(xor, (elem for elem in nums if elem & bit))

        # The other unique value, b, is trivially obtained from a_xor_b and a.
        return [a, a_xor_b ^ a]
