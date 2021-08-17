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
        return Solution._findMinRangeOfFirstCoveringAllSecond(pairs, len(nums))

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
    def _findMinRangeOfFirstCoveringAllSecond(pairs, second_population):
        min_first_range = range(pairs[0][0], pairs[-1][0])
        second_targets = AndCounter(second_population)
        right_iter = iter(pairs)

        with contextlib.suppress(StopIteration):
            for left_first, left_second in pairs:
                while not second_targets:
                    right_first, right_second = next(right_iter)
                    second_targets.add(right_second)

                if right_first - left_first < len(min_first_range):
                    min_first_range = range(left_first, right_first)

                second_targets.remove(left_second)

        return min_first_range.start, min_first_range.stop
