public class Solution {
    public void Solve(char[,] board) {
        var m = board.GetLength(0);
        var n = board.GetLength(1);

        void Protect(int i, int j) {
            if (i != -1 && i != m && j != -1 && j != n && board[i, j] == 'O') {
                board[i, j] = 'P';

                Protect(i - 1, j);
                Protect(i + 1, j);
                Protect(i, j - 1);
                Protect(i, j + 1);
            }
        }

        void ChangeAll(char from, char to) {
            for (var i = 0; i != m; ++i) {
                for (var j = 0; j != n; ++j)
                    if (board[i, j] == from) board[i, j] = to;
            }
        }

        for (var i = 0; i != m; ++i) {
            Protect(i, 0);
            Protect(i, n - 1);
        }

        for (var j = 0; j != n; ++j) {
            Protect(0, j);
            Protect(m - 1, j);
        }

        ChangeAll('O', 'X');
        ChangeAll('P', 'O');
    }
}
