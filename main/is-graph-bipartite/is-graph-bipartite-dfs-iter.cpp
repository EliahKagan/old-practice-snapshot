class Solution {
public:
    static bool isBipartite(const vector<vector<int>>& graph);
};

bool Solution::isBipartite(const vector<vector<int>>& graph)
{
    vector<int> vis (graph.size());
    stack<tuple<int, int>> s; // (vertex, expected color)...
    
    const auto dfs = [&](const int start, const int color) {
        if (vis[start] != 0) return true;
        
        assert(s.empty());
        s.emplace(start, 1);
        
        while (!s.empty()) {
            int src {}, color {};
            tie(src, color) = s.top();
            s.pop();
            
            if (vis[src] == color) continue;
            
            if (vis[src] == -color) return false;
            
            assert(vis[src] == 0);
            vis[src] = color;
            for (const auto dest : graph[src]) s.emplace(dest, -color);
        }
        
        return true;
    };
    
    for (auto start = 0; start != graph.size(); ++start)
        if (!dfs(start, 1)) return false;
    
    return true;
}
