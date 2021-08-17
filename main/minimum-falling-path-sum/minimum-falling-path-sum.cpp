class Solution {
public:
    static int minFallingPathSum(vector<vector<int>>& a) noexcept;
};

int Solution::minFallingPathSum(vector<vector<int>>& a) noexcept
{
    const auto n = a.size();

    for (auto i = 1; i != n; ++i) {
        a[i][0] += min(a[i - 1][0], a[i - 1][1]);

        for (auto j = 1; j != n - 1; ++j)
            a[i][j] += min(a[i - 1][j], min(a[i - 1][j - 1], a[i - 1][j + 1]));

        a[i][n - 1] += min(a[i - 1][n - 2], a[i - 1][n - 1]);
    }

    return *min_element(cbegin(a.back()), cend(a.back()));
}
