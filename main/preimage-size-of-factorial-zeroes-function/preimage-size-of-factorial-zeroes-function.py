class OnDemandList:
    def __init__(self, size, selector):
        self._size = size
        self._selector = selector

    def __len__(self):
        return self._size

    def __getitem__(self, index):
        if not 0 <= index < self._size:
            raise IndexError('index out of range')

        return self._selector(index)

    def resize(size):
        self._size = size

def countFactorsInSpan(span, factor):
    count = 0
    while span > 0:
        span //= factor
        count += span
    return count

def computeFZF(n):
    return countFactorsInSpan(n, 5)

fzf = OnDemandList(4000000021, computeFZF) # computeFZF(4000000020)==1000000001

class Solution:
    def preimageSizeFZF(self, count):
        """
        :type count: int
        :rtype: int
        """
        return bisect.bisect_right(fzf, count) - bisect.bisect_left(fzf, count)
