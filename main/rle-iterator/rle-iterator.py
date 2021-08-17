class RLEIterator:
    def __init__(self, a):
        """
        :type A: List[int]
        """
        self._rle = a
        self._pos = 0
        self._cnt = 0

    def next(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n <= 0:
            raise IndexError('n must be strictly positive')
        
        try:
            # If we have at least n - 1 more of the current item, just use that.
            if self._cnt + n <= self._rle[self._pos]:
                self._cnt += n
                return self._rle[self._pos + 1]
            
            # Use up the rest of the current item (if any) and move to the next item.
            n -= self._rle[self._pos] - self._cnt
            self._pos += 2
            self._cnt = 0
            
            # Exhaust items that can be fully exhausted.
            while self._rle[self._pos] < n:
                n -= self._rle[self._pos]
                self._pos += 2
            
            # Partially exhaust the current item and return it.
            self._cnt = n
            return self._rle[self._pos + 1]
        except IndexError:
            # If we fell off the end, then there are no more elements.
            return RLEIterator._NO_ELEMENT
    
    _NO_ELEMENT = -1


# Your RLEIterator object will be instantiated and called as such:
# obj = RLEIterator(A)
# param_1 = obj.next(n)
