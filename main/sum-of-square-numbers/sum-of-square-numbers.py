class Solution:
    def judgeSquareSum(self, c):
        """
        :type c: int
        :rtype: bool
        """
        history = set()
        squares = (i * i for i in itertools.count())

        for term in itertools.takewhile(lambda t : t <= c, squares):
            if c - term in history or term * 2 == c:
                return True
            history.add(term)

        return False
