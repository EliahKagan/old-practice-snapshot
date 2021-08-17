# Definition for a point.
# class Point:
#     def __init__(self, a=0, b=0):
#         self.x = a
#         self.y = b

from collections import Counter
from fractions import Fraction

def slope(p, q):
    try:
        return Fraction(q.y - p.y, q.x - p.x)
    except ZeroDivisionError:
        if q.y == p.y:
            raise
        return None

class Solution:
    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        if not points:
            return 0

        best = 0
        for i in range(len(points) - 1):
            counts = Counter()
            for j in range(i + 1, len(points)):
                counts[slope(points[i], points[j])] += 1
            best = max(best, counts.most_common(1)[0][1])

        return best + 1
