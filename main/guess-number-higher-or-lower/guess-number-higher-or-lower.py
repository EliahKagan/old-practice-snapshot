# The guess API is already defined for you.
# @param num, your guess
# @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
# def guess(num):

class SequenceWrapper(object):
    def __init__(self, function, start, stop):
        self._function = function
        self._start = start
        self._size = max(0, stop - start)
    
    def __len__(self):
        return self._size
    
    def __getitem__(self, index):
        if index < self._size:
            return self._function(self._start + index)
        raise IndexError('index out of range')

class Solution(object):
    def guessNumber(self, n):
        """
        :type n: int
        :rtype: int
        """
        a = SequenceWrapper(lambda i: -guess(i), 1, n + 1)
        return bisect.bisect_left(a, 0) + 1
