import itertools
import math
import sys

class Solution:
    def judgeSquareSum(self, c):
        """
        :type c: int
        :rtype: bool
        """
        half = c // 2
        if int(math.sqrt(half))**2 == half:
            return True

        history = set()
        squares = (i * i for i in itertools.count())

        for term in itertools.takewhile(lambda t : t <= half, squares):
            print('[ ' + str(term) + ' ]', file=sys.stderr)
            if c - term in history:
                return True
            history.add(term)

        return False
