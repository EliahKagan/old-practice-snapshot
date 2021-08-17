squares = [0]

class Solution:
    def mySqrt(self, x):
        """
        :type x: int
        :rtype: int
        """
        while squares[-1] < x:
            squares.append(len(squares)**2)

        return bisect.bisect_right(squares, x) - 1
