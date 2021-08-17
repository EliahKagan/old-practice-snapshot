class Solution {
public:
    static constexpr int totalNQueens(int n);
};

namespace {
    constexpr auto nmax = 128;

    constexpr bool safe(const int (&qjs)[nmax], const int i)
    {
        for (auto qi = 0; qi != i; ++qi) {
            const auto dj = qjs[i] - qjs[qi];
            if (dj == 0 || i - qi == abs(dj)) return false;
        }

        return true;
    }
}

constexpr int Solution::totalNQueens(const int n)
{
    auto acc = 0;
    int qjs[nmax] {-1};

    for (auto i = 0; i != -1; ) {
        if (++qjs[i] == n)
            --i; // retreat
        else if (!safe(qjs, i))
            continue;
        else if (i == n - 1)
            ++acc;
        else
            qjs[++i] = -1; // advance
    }

    return acc;
}
