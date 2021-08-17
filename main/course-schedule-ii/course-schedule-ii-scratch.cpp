#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

using namespace std;

class Solution {
public:
    static vector<int> findOrder(int numCourses,
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
    
    // Visitation states for directed graph traversal.
    enum class Color {
        white,  // unvisited
        gray,   // visited but not fully explored
        black   // visited and fully explored
    };
    
    // Performs reverse topological sort by depth-first traversal.
    // When the graph is cyclic, returns an empty vector.
    vector<int> reverse_topological_sort(const vector<vector<int>>& adj)
    {
        vector<int> out;
        out.reserve(adj.size());
        
        vector<Color> vis (adj.size());
        
        // Tells if a directed graph has a cycle. For as long as no cycle is
        // found, also builds a reverse topological sort as it retreats.
        const function<bool(int)> has_cycle_from = [&](const int cur) {
            switch (vis[cur]) {
            case Color::white:
                {
                    vis[cur] = Color::gray;
                    
                    const auto& row = adj[cur];
                    if (any_of(cbegin(row), cend(row), has_cycle_from))
                        return true;
                    
                    vis[cur] = Color::black;
                    out.push_back(cur);
                    return false;
                }

            case Color::gray:
                return true;

            case Color::black:
                return false;
            }
        };
        
        for (auto start = 0; start != adj.size(); ++start) {
            if (has_cycle_from(start)) {
                out.clear();
                break;
            }
        }
        
        return out;
    }
}

vector<int> Solution::findOrder(const int numCourses,
                                const vector<pair<int, int>>& prerequisites)
{
    const auto adj = build_adjacency_list(numCourses, prerequisites);
    return reverse_topological_sort(adj);
}
