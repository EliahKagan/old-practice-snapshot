class Solution(object):  # a Python 2 solution
    def change(self, amount, coins):
        """
        :type amount: int
        :type coins: List[int]
        :rtype: int
        """
        length = len(coins)
        memo = {}

        def ways(subtot, index):
            if subtot == 0:
                return 1

            if index == length:
                return 0

            key = (subtot, index)
            try:
                return memo[key]
            except KeyError:
                value = coins[index]
                index += 1
                count = 0

                while subtot >= 0:
                    count += ways(subtot, index)
                    subtot -= value

                memo[key] = count
                return count

        return ways(amount, 0)
