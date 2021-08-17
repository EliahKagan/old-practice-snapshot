class Solution:
    @staticmethod
    def isRectangleOverlap(rec1, rec2):
        """
        :type rec1: List[int]
        :type rec2: List[int]
        :rtype: bool
        """
        # aCN is the C-coordinate of the lower-left vertex of recN
        # bCN is the C-coorindate of the upper-right vertex of recN
        ax1, ay1, bx1, by1 = rec1
        ax2, ay2, bx2, by2 = rec2
        assert ax1 <= bx1 and ay1 <= by1 and ax2 <= bx2 and ay2 <= by2

        return not (bx1 <= ax2 or bx2 <= ax1  # non-overlapping x-projections
                    or by1 <= ay2 or by2 <= ay1)  # non-overlapping y-projections
