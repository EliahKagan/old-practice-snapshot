import contextlib

class AndCounter:
    '''Tracks frequencies of items and knows if it has at least one of each.'''
    def __init__(self, size):
        self._counts = [0] * size
        self._missing = size

    def __bool__(self):
        return not self._missing

    def add(self, item):
        if not self._counts[item]:
            self._missing -= 1
        self._counts[item] += 1

    def remove(self, item):
        self._counts[item] -= 1
        if not self._counts[item]:
            self._missing += 1

class Solution:
    @staticmethod
    def smallestRange(nums):
        """
        :type nums: List[List[int]]
        :rtype: List[int]
        """
        pairs = Solution._markChainAndSort(nums)
        return Solution._findMinRangeCoveringAllGroups(pairs, len(nums))

    @staticmethod
    def _markElementsByRow(nums):
        for i, row in enumerate(nums):
            fixed_i = i # so later iterations don't affect "earlier" results
            yield ((elem, fixed_i) for elem in row)

    @staticmethod
    def _markChainAndSort(nums):
        groups = Solution._markElementsByRow(nums)
        chain = itertools.chain.from_iterable(groups)
        return sorted(chain, key=operator.itemgetter(0))

    @staticmethod
    def _findMinRangeCoveringAllGroups(pairs, group_count):
        min_range = range(2**63 - 1)
        targets = AndCounter(group_count)
        right_iter = iter(pairs)
        left_iter = iter(pairs)

        with contextlib.suppress(StopIteration):
            while True:
                while not targets:
                    right_value, group = next(right_iter)
                    targets.add(group)

                while targets:
                    left_value, group = next(left_iter)
                    targets.remove(group)

                if right_value - left_value < len(min_range):
                    min_range = range(left_value, right_value)

        return min_range.start, min_range.stop
