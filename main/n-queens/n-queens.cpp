class Solution {
public:
    static vector<vector<string>> solveNQueens(size_t n);
};

vector<vector<string>> Solution::solveNQueens(const size_t n)
{
    vector<vector<string>> ans;
    vector<string> board (n, string(n, '.'));

    const auto hitscan = [n, &board](const size_t i, const size_t j) {
        for (size_t h {0u}; h != i; ++h)
            if (board[h][j] == 'Q') return true;

        for (auto h = i, k = j; --h < n && --k < n; )
            if (board[h][k] == 'Q') return true;

        for (auto h = i, k = j; --h < n && ++k < n; )
            if (board[h][k] == 'Q') return true;

        return false;
    };

    const function<void(size_t)>
    dfs {[n, &ans, &board, hitscan, &dfs](const size_t i) {
        if (i == n) {
            ans.push_back(board);
            return;
        }

        for (size_t j {0u}; j != n; ++j) {
            if (hitscan(i, j)) continue;

            board[i][j] = 'Q';
            dfs(i + 1u);
            board[i][j] = '.';
        }
    }};

    dfs(0u);
    return ans;
}
