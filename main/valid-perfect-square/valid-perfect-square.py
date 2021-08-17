squares = [0]

class Solution:
    def isPerfectSquare(self, num):
        """
        :type num: int
        :rtype: bool
        """
        while squares[-1] < num:
            squares.append(len(squares)**2)

        i = bisect.bisect_left(squares, num)
        return squares[i] == num
