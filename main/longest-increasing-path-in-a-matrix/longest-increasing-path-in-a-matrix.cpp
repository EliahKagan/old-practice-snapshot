class Solution {
public:
    static int longestIncreasingPath(const vector<vector<int>>& matrix);
};

namespace {
    vector<vector<unsigned>>
    build_adjacency_list(const vector<vector<int>>& matrix)
    {
        const auto m = static_cast<unsigned>(matrix.size());
        const auto n = static_cast<unsigned>(matrix.front().size());
        vector<vector<unsigned>> adj (m * n);
        
        const auto try_connect =
        [&matrix, m, n, &adj](const unsigned i, const unsigned j,
                              const unsigned h, const unsigned k) {
            if (h < m && k < n && matrix[i][j] < matrix[h][k])
                adj[i * n + j].push_back(h * n + k);
        };
        
        for (unsigned i {0}; i != m; ++i) {
            for (unsigned j {0}; j != n; ++j) {
                try_connect(i, j, i, j - 1);
                try_connect(i, j, i, j + 1);
                try_connect(i, j, i - 1, j);
                try_connect(i, j, i + 1, j);
            }
        }
        
        return adj;
    }
    
    int max_path_length(const vector<vector<unsigned>>& adj)
    {
        static constexpr auto unknown = -1;
        vector<int> memo (adj.size(), unknown);
        
        const auto dfs = [&adj, &memo](const auto& me, const size_t src) {
            auto length = memo[src];
            if (length != unknown) return length;
            
            length = 0;
            for (const auto dest : adj[src])
                length = max(length, me(me, dest));
            
            return memo[src] = ++length;
        };
        
        auto acc = 0;
        
        const auto size = adj.size();
        for (size_t start {0}; start != size; ++start)
            acc = max(acc, dfs(dfs, start));
        
        return acc;
    }
}

int Solution::longestIncreasingPath(const vector<vector<int>>& matrix)
{
    if (matrix.empty()) return 0;
    
    const auto adj = build_adjacency_list(matrix);
    return max_path_length(adj);
}
