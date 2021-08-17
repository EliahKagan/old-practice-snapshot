class Solution {
public:
    static bool canFinish(int numCourses,
                          const vector<pair<int, int>>& prerequisites);
};

namespace {
    vector<vector<int>>
    build_adjacency_list(const int vertex_count,
                         const vector<pair<int, int>>& edges)
    {
        vector<vector<int>> adj (vertex_count);
        
        for (const auto edge : edges) {
            assert(0 <= edge.first && edge.first < vertex_count);
            assert(0 <= edge.second && edge.second < vertex_count);
            adj[edge.first].push_back(edge.second);
        }
        
        return adj;
    }
    
    enum class Color {
        white,  // unvisited
        gray,   // visited but not fully explored
        black   // fully explored
    };
    
    bool has_cycle(const vector<vector<int>>& adj)
    {
        vector<Color> vis (adj.size());
        
        const function<bool(int)> has_cycle_from = [&](const int src) {
            switch (vis[src]) {
            case Color::white:
                {
                    vis[src] = Color::gray;

                    const auto& row = adj[src];
                    if (any_of(cbegin(row), cend(row), has_cycle_from))
                        return true;

                    vis[src] = Color::black;
                    return false;
                }

            case Color::gray:
                return true;

            case Color::black:
                return false;
            }
        };
        
        for (auto start = 0; start != adj.size(); ++start)
            if (has_cycle_from(start)) return true;
        
        return false;
    }
}

bool Solution::canFinish(int numCourses,
                         const vector<pair<int, int>>& prerequisites)
{
    return !has_cycle(build_adjacency_list(numCourses, prerequisites));
}
