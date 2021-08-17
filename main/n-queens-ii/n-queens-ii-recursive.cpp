class Solution {
public:
    static int totalNQueens(int n);
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
    
    int dfs(vector<int>& qjs, const int i)
    {
        const auto n = qjs.size();
        
        if (i == n) return 1;
        
        auto acc = 0;
        
        for (auto j = 0; j != n; ++j) {
            if (safe(qjs, i, j)) {
                qjs[i] = j;
                acc += dfs(qjs, i + 1);
            }
        }
        
        return acc;
    }
}

int Solution::totalNQueens(const int n)
{
    vector<int> qjs (n);
    return dfs(qjs, 0);
}
