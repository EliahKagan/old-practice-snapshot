class Solution:
    def subsets(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        powerset = [[]]

        for singleton in ([element] for element in nums):
            for subset in itertools.islice(powerset, len(powerset)):
                powerset.append(subset + singleton)

        return powerset
