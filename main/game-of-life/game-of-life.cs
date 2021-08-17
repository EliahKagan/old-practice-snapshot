public class Solution {
    public void GameOfLife(int[,] board) {
        const int old_bit = 1, new_bit = old_bit << 1;

        var m = board.GetLength(0);
        var n = board.GetLength(1);
        if (m == 0 || n == 0) return;

        int Get(int i, int j)
            => (0 <= i && i < m && 0 <= j && j < n ? (board[i, j] & old_bit)
                                                   : 0);

        for (var i = 0; i != m; ++i) {
            for (var j = 0; j != n; ++j) {
                var pop = Get(i - 1, j - 1) + Get(i - 1, j) + Get(i - 1, j + 1)
                            + Get(i, j - 1) + Get(i, j + 1) + Get(i + 1, j - 1)
                            + Get(i + 1, j) + Get(i + 1, j + 1);

                if (pop == 3 || (pop == 2 && ((board[i, j] & old_bit) != 0)))
                    board[i, j] |= new_bit;
            }
        }

        for (var i = 0; i != m; ++i)
            for (var j = 0; j != n; ++j) board[i, j] >>= 1;
    }
}
