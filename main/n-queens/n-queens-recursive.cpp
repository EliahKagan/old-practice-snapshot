class Solution {
public:
    static vector<vector<string>> solveNQueens(int n);
};

namespace {
    inline bool safe(const vector<int>& qjs, const int i, const int j) noexcept
    {
        for (auto qi = 0; qi != i; ++qi) {
            const auto dj = j - qjs[qi];
            if (dj == 0 || i - qi == abs(dj)) return false;
        }
        
        return true;
    }
    
    vector<string> draw(const vector<int>& qjs)
    {
        const auto n = qjs.size();
        
        vector<string> board (n, string(n, '.'));
        for (auto i = 0; i != n; ++i) board[i][qjs[i]] = 'Q';
        return board;
    }
    
    void dfs(vector<vector<string>>& boards, vector<int>& qjs, const int i)
    {
        const auto n = qjs.size();
        
        if (i == n) {
            boards.push_back(draw(qjs));
            return;
        }
        
        for (auto j = 0; j != n; ++j) {
            if (safe(qjs, i, j)) {
                qjs[i] = j;
                dfs(boards, qjs, i + 1);
            }
        }
    }
}

vector<vector<string>> Solution::solveNQueens(const int n)
{
    vector<vector<string>> boards;
    vector<int> qjs (n);
    dfs(boards, qjs, 0);
    return boards;
}
