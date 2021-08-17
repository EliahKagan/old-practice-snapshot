#!/usr/bin/env python3

import collections
import contextlib
import heapq
import sys

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
                    #print(right_value, end=' ', file=sys.stderr) # for debugging
                    targets.add(row)

                while targets:
                    left_value, row = merger.dequeue()
                    targets.remove(row)

                if right_value - left_value < len(min_range):
                    min_range = range(left_value, right_value)

        return min_range.start, min_range.stop

nums = [[-39188, -19118],
        [-92167, -74585, -71372, -68941, -66699, -66541, -65520, -61363, -47182, -42837, -42606, -4518, 12948, 18858, 24820, 36209, 55066, 64917, 65611, 82101, 90910, 91233],
        [-54216, -22937, -17115, -1603, 2167, 36929],
        [-94402, -57858, -48916, -38906, -27238, -615, 43439, 57426, 88482],
        [-90879, -88451, -86193, -84039, -83226, -82043, -76734, -70728, -68704, -64036, -61383, -56726, -56542, -50342, -40026, -29768, -27798, -25701, -22833, -21175, -18805, -17066, -16382, -1192, 1599, 7103, 7759, 12194, 19076, 24753, 30678, 31160, 47688, 53150, 56513, 57693, 58054, 58876, 61753, 66660, 67005, 69236, 70360, 77765, 80622, 85875, 87923, 89693, 91719, 93501, 93756, 93965, 98746, 98751, 99624],
        [-93492, -75274, -75042, -73965, -70584, -67383, -62776, -59901, -47608, -46677, -46256, -22718, -13115, -12702, -11416, -10030, -7529, 1512, 5804, 8803, 12381, 19380, 24865, 24983, 28389, 39141, 42273, 45040, 59032, 73663, 74333, 82422, 87044, 87495, 93470, 97758, 99008],
        [-99615, -96435, -94713, -84516, -84092, -83271, -83196, -82663, -81339, -79318, -72884, -72814, -72266, -72059, -63513, -59654, -54579, -53893, -48416, -48342, -44555, -34252, -21257, -20760, -17101, -17093, -16354, -13770, -5325, -2980, -2047, -2041, -1876, 5721, 5850, 7217, 15316, 18064, 18490, 24318, 30518, 37714, 38240, 43405, 47303, 47405, 56965, 60219, 62012, 64024, 68853, 68948, 68987, 71759, 72264, 74765, 76709, 86777, 86947, 87933, 97352],
        [-91797, -87698, -84590, -81956, -74207, -73699, -72692, -72516, -67008, -62520, -61792, -61466, -53035, -44200, -36235, -30447, -27236, -21593, -20133, -17521, -14713, -13694, -12818, -2842, -424, 6649, 10498, 12692, 17478, 26721, 27276, 28361, 30913, 41900, 50333, 52277, 53232, 57268, 57832, 67006, 78180, 78218, 81042, 86146, 86596, 89450],
        [-99254, -91367, -90384, -89507, -88167, -87488, -86508, -85257, -85130, -84787, -80724, -80327, -79068, -78644, -74888, -72647, -70801, -66180, -65235, -65118, -65013, -63480, -62578, -57156, -54835, -50920, -50626, -48537, -48472, -48267, -39760, -38004, -37883, -36034, -33527, -31950, -31155, -28798, -25985, -25818, -22702, -21719, -15520, -15037, -6593, -4347, -4307, -3746, -3170, 1567, 5657, 8100, 10270, 10644, 12976, 14458, 15675, 17582, 18572, 20304, 25305, 31757, 36520, 37121, 37713, 39530, 40236, 47942, 49216, 51242, 53337, 53540, 54578, 54726, 55794, 57054, 58971, 63471, 65853, 66177, 69514, 71366, 72327, 77827, 80458, 88078, 90180, 99435],
        [-99151, -99088, -98736, -97673, -93228, -91944, -89724, -88227, -83589, -81754, -73969, -71481, -69545, -65356, -65102, -64856, -62760, -60762, -52006, -41822, -41358, -38876, -38859, -35006, -32955, -32428, -28461, -26913, -24750, -24402, -13879, -10037, -9195, -8813, -7855, -7803, -7018, 1325, 4867, 6159, 6660, 7408, 8698, 9357, 12014, 14452, 15286, 17541, 18985, 20299, 22094, 32151, 32639, 32876, 35112, 35430, 36474, 41235, 42697, 47930, 48244, 49223, 54219, 55905, 56246, 61192, 62996, 67282, 68255, 68290, 69327, 69411, 70766, 72956, 77598, 78926, 79286, 84743, 85207, 89352, 90524, 93217, 93402, 94572, 96726, 97263]]

print(Solution.smallestRange(nums))
