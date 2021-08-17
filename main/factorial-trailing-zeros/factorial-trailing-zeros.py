def countFactors(n, k):
    count = 0
    while n > 0:
        n //= k
        count += n
    return count

class Solution:
    def trailingZeroes(self, n):
        """
        :type n: int
        :rtype: int
        """
        return countFactors(n, 5)
