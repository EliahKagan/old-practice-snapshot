class Solution {
public:
    vector<int> findOrder(int numCourses,
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
    
    queue<int> get_initial_leaves(const vector<vector<int>>& adj)
    {
        queue<int> leaves;
        
        for (auto u = 0; i != adj.size(); ++u)
            if (adj[u].empty()) leaves.push(u);
        
        return leaves;
    }
    
    // Performs reverse topological sort by an analogue of Kahn's algorithm.
    vector<int> reverse_topological_sort(vector<vector<int>>& adj)
    {
        vector<int> ret;
        ret.reserve(adj.size());
        
        for (auto leaves = get_initial_leaves(adj); !leaves.empty(); ) {
            
        }
        
        return ret;
    }
}

vector<int>
Solution::findOrder(const int numCourses,
                    const vector<pair<int, int>>& prerequisites)
{
    auto adj = build_adjacency_list(numCourses, prerequisites);
    return reverse_topological_sort(adj);
}
