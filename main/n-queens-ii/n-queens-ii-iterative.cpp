class Solution {
public:
    static int totalNQueens(int n);
};

namespace {
    inline bool safe(const vector<int>& qjs)
    {
        const auto i = static_cast<int>(qjs.size() - 1);
        const auto j = qjs.back();
        
        for (auto qi = 0; qi != i; ++qi) {
            const auto dj = j - qjs[qi];
            if (dj == 0 || i - qi == abs(dj)) return false;
        }
        
        return true;
    }
}

int Solution::totalNQueens(const int n)
{
    assert(n > 0);
    
    vector<int> qjs;
    qjs.reserve(n);
    qjs.push_back(-1);
    
    auto acc = 0;
    
    while (!qjs.empty()) {
        if (++qjs.back() == n)
            qjs.pop_back();
        else if (!safe(qjs))
            continue;
        else if (qjs.size() == n)
            ++acc;
        else
            qjs.push_back(-1);
    }
    
    return acc;
}
