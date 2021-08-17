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
    
    struct Frame {
        int vertex; // the current vertex
        int index;  // index into its row in the adjacency list
    };
    
    bool has_cycle(const vector<vector<int>>& adj)
    {
        vector<Color> vis (adj.size());
        stack<Frame> frames; // reusing stack for fewer allocations
        
        const auto has_cycle_from = [&](const int start) {
            if (vis[start] == Color::black) return false;
            
            assert(vis[start] == Color::white);
            vis[start] = Color::gray;
            
            assert(frames.empty());
            frames.push({start, 0});
            
            while (!frames.empty()) {
                auto& frame = frames.top();
                const auto& row = adj[frame.vertex];
                
                if (frame.index == row.size()) { // retreat
                    vis[frame.vertex] = Color::black;
                    frames.pop();
                    continue;
                }
                
                const auto dest = row[frame.index++];
                
                switch (vis[dest]) {
                case Color::white: // advance
                    vis[dest] = Color::gray;
                    frames.push({dest, 0});
                    break;

                case Color::gray:
                    return true;

                case Color::black:
                    break;
                }
                
            }
            
            return false;
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
