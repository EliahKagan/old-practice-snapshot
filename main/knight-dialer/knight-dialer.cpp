class Solution {
public:
    static int knightDialer(int n) noexcept;
};

namespace {
    constexpr auto order = 10; // number of vertices

    constexpr auto max_degree = 3;

    constexpr auto stop_mark = -1;

    constexpr array<array<int, max_degree + 1>, order> adj {{
        {{4, 6, stop_mark, stop_mark}},                 // 0
        {{6, 8, stop_mark, stop_mark}},                 // 1
        {{7, 9, stop_mark, stop_mark}},                 // 2
        {{4, 8, stop_mark, stop_mark}},                 // 3
        {{0, 3, 9, stop_mark}},                         // 4
        {{stop_mark, stop_mark, stop_mark, stop_mark}}, // 5
        {{0, 1, 7, stop_mark}},                         // 6
        {{2, 6, stop_mark, stop_mark}},                 // 7
        {{1, 3, stop_mark, stop_mark}},                 // 8
        {{2, 4, stop_mark, stop_mark}}                  // 9
    }};

    array<array<int, 10>, 5001> dp {{
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
        {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}}
    }};

    auto last_row_computed = 1;

    constexpr auto mod = 1'000'000'007LL;

    void compute(const int i)
    {
        const auto& prev = dp[i - 1];
        auto& cur = dp[i];

        for (auto j = 0; j != order; ++j) {
            auto acc = 0LL;

            for (auto p = cbegin(adj[j]); *p != stop_mark; ++p)
                acc += prev[*p];

            cur[j] = static_cast<int>(acc % mod);
        }
    }
}

int Solution::knightDialer(const int n) noexcept
{
    while (last_row_computed < n) compute(++last_row_computed);

    const auto& row = dp[n];
    return static_cast<int>(accumulate(cbegin(row), cend(row), 0LL) % mod);
}
