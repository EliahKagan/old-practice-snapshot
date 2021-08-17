class Solution:
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        paid = math.inf
        profit = 0

        for price in prices:
            if paid < price:
                profit = max(profit, price - paid)
            else:
                paid = price

        return profit
