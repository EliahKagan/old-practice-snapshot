# Definition for a point.
# class Point:
#     def __init__(self, a=0, b=0):
#         self.x = a
#         self.y = b

from collections import Counter
from fractions import Fraction

def slope(p, q):
    px, py = p
    qx, qy = q
    try:
        return Fraction(qy - py, qx - px)
    except ZeroDivisionError:
        if qy == py:
            raise
        return None

class Solution:
    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """
        point_counts = Counter((p.x, p.y) for p in points)
        points = tuple(point_counts)

        best = 0
        for i in range(len(points)):
            p = points[i]
            slope_counts = Counter()
            cur = 0

            for j in range(i + 1, len(points)):
                q = points[j]
                sl = slope(p, q)
                sc = slope_counts[sl] + point_counts[q]
                slope_counts[sl] = sc
                cur = max(cur, sc)

            best = max(best, cur + point_counts[p])

        return best
