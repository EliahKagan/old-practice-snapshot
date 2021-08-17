class Solution:
    def sortArrayByParityII(self, a):
        """
        :type A: List[int]
        :rtype: List[int]
        """
        evens = (x for x in a if x % 2 == 0)
        odds = (x for x in a if x % 2 == 1)
        return list(itertools.chain.from_iterable(zip(evens, odds)))
