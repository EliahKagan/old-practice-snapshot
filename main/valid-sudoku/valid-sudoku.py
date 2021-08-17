from itertools import chain

RECT_LEN = 3
RECT_AREA = RECT_LEN**2

class Solution:
    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """
        return all(map(self._cellsAreUnique, self._getRects(board)))

    def _cellsAreUnique(self, cells):
        a = [c for c in cells if c != '.']
        return len(a) == len(set(a))

    def _getRects(self, board):
        for row in board:
            yield row
        for col in zip(*board):
            yield col
        for subBox in self._getAllSubBoxes(board):
            yield subBox

    def _getAllSubBoxes(self, board):
        for istart in range(0, RECT_AREA, RECT_LEN):
            for jstart in range(0, RECT_AREA, RECT_LEN):
                yield self._getSubBox(board, istart, jstart)

    def _getSubBox(self, board, istart, jstart):
        for i in range(istart, istart + RECT_LEN):
            for j in range(jstart, jstart + RECT_LEN):
                yield board[i][j]
