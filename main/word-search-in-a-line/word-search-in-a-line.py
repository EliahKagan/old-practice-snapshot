class Solution:
    def exist(self, board, word):
        """
        :type board: List[List[str]]
        :type word: str
        :rtype: bool
        """
        return (any(word in row for row in self._rows(board))
                or any (word in col for col in self._cols(board)))

    def _rows(self, board):
        return (''.join(row) for row in board)

    def _cols(self, board):
        return (''.join(col) for col in zip(*board))
