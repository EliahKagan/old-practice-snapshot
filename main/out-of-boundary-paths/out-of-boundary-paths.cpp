class Solution {
public:
    static int findPaths(int m, int n, int d, int i, int j);
};

namespace {
    vector<vector<int>> make_empty_grid(const int height, const int width)
    {
        return vector<vector<int>>(height, vector<int>(width));
    }

    const auto fill_ones = [](vector<int>& row) noexcept {
        fill(begin(row), end(row), 1);
    };

    const auto pad_ones = [](vector<int>& row) noexcept {
        row.front() = row.back() = 1;
    };

    vector<vector<int>> make_initial_counts(const int height, const int width)
    {
        auto dp = make_empty_grid(height, width);

        fill_ones(dp.front());
        fill_ones(dp.back());

        for_each(next(begin(dp)), prev(end(dp)), pad_ones);

        return dp;
    }

    constexpr auto mod = 1'000'000'007LL;

    void update(vector<vector<int>>& dp, vector<vector<int>>& aux) noexcept
    {
        aux = dp;

        const auto istop = static_cast<int>(dp.size() - 1);
        const auto jstop = static_cast<int>(dp.front().size() - 1);

        for (auto i = 1; i != istop; ++i) {
            for (auto j = 1; j != jstop; ++j) {
                auto x = 0LL;

                x += aux[i - 1][j];
                x += aux[i + 1][j];
                x += aux[i][j - 1];
                x += aux[i][j + 1];

                dp[i][j] = static_cast<int>(x % mod);
            }
        }
    }
}

int Solution::findPaths(const int m, const int n, int d,
                        const int i, const int j)
{
    const auto height = m + 2, width = n + 2;

    auto dp = make_initial_counts(height, width);
    auto aux = make_empty_grid(height, width);

    while (d-- > 0) update(dp, aux);

    return dp[i + 1][j + 1];
}
