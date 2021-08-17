class Solution:
    def __init__(self):
        self._INT_MIN = -2**31
        self._INT_MAX = 2**31 - 1

    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """
        if x < 0:
            result = -int(''.join(reversed(str(x)[1:])))
            return 0 if result < self._INT_MIN else result
        else:
            result = int(''.join(reversed(str(x))))
            return 0 if result > self._INT_MAX else result
