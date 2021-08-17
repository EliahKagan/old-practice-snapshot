class KthLargest:
    """Data strcure to finds kth largest element in a stream, for fixed k."""
    
    __slots__ = ('_k', '_heap')
    
    def __init__(self, k: int, nums: List[int]):
        """Creates the data structure with the given k, starting with nums."""
        self._k = k
        self._heap = nums[:self._k]
        
        heapq.heapify(self._heap)
        
        for val in nums[self._k:]:
            heapq.heappushpop(self._heap, val)
        
        assert len(self._heap) <= self._k

    def add(self, val: int) -> int:
        """Receives val from the stream. Finds the new kth largest element."""
        if len(self._heap) == self._k:
            heapq.heappushpop(self._heap, val)
        else:
            assert len(self._heap) < self._k, 'kept too many elements'
            heapq.heappush(self._heap, val)
        
        return self._heap[0]
        

# Your KthLargest object will be instantiated and called as such:
# obj = KthLargest(k, nums)
# param_1 = obj.add(val)
