class Solution {
public:
    int findCircleNum(vector<vector<int>>& a) {
        const auto n = a.size();
        if (n == 0u) return 0;

        const function<void(size_t)> dfs = [&dfs, &a, n](const size_t i) {
            a[i][i] = 0;

            for (size_t j {0u}; j != n; ++j) {
                if (a[i][j] && a[j][j]) {
                    a[i][j] = a[j][i] = 0;
                    dfs(j);
                }
            }
        };

        auto count = 0;

        for (size_t i {0u}; i != n; ++i) {
            if (a[i][i]) {
                dfs(i);
                ++count;
            }
        }

        return count;
    }
};
