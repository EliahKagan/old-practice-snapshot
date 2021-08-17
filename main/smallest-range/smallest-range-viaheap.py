import contextlib

class MergingQueue:
    '''Maintains a queue into which already-sorted rows are merged in order.'''
    def __init__(self, rows):
        self._iterators = tuple(map(iter, rows))
        self._heap = []
        self._acquire_each()
        self._queue = collections.deque()

    def enqueue(self):
        '''Expands the queue rightward and returns the newly added pair.'''
        pair = self._dispense()
        self._queue.append(pair)
        return pair

    def dequeue(self):
        '''Contracts the queue leftward and returns the newly removed pair.'''
        return self._queue.popleft()

    def _acquire_each(self):
        for i, it in enumerate(self._iterators):
            with contextlib.suppress(StopIteration):
                heapq.heappush(self._heap, (next(it), i))

    def _acquire(self, i):
        with contextlib.suppress(StopIteration):
            heapq.heappush(self._heap, (next(self._iterators[i]), i))

    def _dispense(self):
        pair = _e, i = heapq.heappop(self._heap)
        self._acquire(i)
        return pair

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
        min_range = range(2**63 - 1)
        targets = AndCounter(len(nums))
        merger = MergingQueue(nums)

        with contextlib.suppress(IndexError):
            while True:
                while not targets:
                    right_value, row = merger.enqueue()
                    targets.add(row)

                while targets:
                    left_value, row = merger.dequeue()
                    targets.remove(row)

                if right_value - left_value < len(min_range):
                    min_range = range(left_value, right_value)

        return min_range.start, min_range.stop
