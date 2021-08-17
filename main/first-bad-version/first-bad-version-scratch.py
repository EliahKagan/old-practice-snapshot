import bisect

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
    def firstBadVersion(self, n):
        """
        :type n: int
        :rtype: int
        """
        a = SequenceWrapper(isBadVersion, 1, n + 1)
        return bisect.bisect_left(a, True) + 1

def isBadVersion(i):
    print 'isBadVersion(%d)' % i
    return i >= 1000000000000
