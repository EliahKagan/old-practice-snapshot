class Solution {
public:
    static vector<int> findOrder(int numCourses,
                                 const vector<pair<int, int>>& prerequisites);
};

namespace {
    class Graph {
    public:
        explicit Graph(int vertex_count);
        void add_edge(int src, int dest);
        vector<int> topological_sort() &&; // Kahn's algorithm
        
    private:
        queue<int> get_roots() const;
        vector<int> do_topological_sort();
        
        vector<vector<int>> adj_;
        vector<int> indegrees_;
        int vertex_count_;
    };
    
    Graph::Graph(const int vertex_count) : adj_(vertex_count),
                                           indegrees_(vertex_count),
                                           vertex_count_{vertex_count}
    {
    }
    
    void Graph::add_edge(const int src, const int dest)
    {
        assert(0 <= src && src < vertex_count_);
        assert(0 <= dest && dest < vertex_count_);
        adj_[src].push_back(dest);
        ++indegrees_[dest];
    }
    
    vector<int> Graph::topological_sort() &&
    {
        auto ret = do_topological_sort();
        
        if (ret.size() != vertex_count_) {
            assert(ret.size() < vertex_count_);
            ret.clear();
            ret.shrink_to_fit();
        }
        
        return ret;
    }
    
    queue<int> Graph::get_roots() const
    {
        queue<int> roots;
        
        for (auto u = 0; u != vertex_count_; ++u)
            if (indegrees_[u] == 0) roots.push(u);
        
        return roots;
    }
    
    vector<int> Graph::do_topological_sort()
    {
        vector<int> ret;
        ret.reserve(vertex_count_);
        
        for (auto roots = get_roots(); !roots.empty(); ) {
            const auto src = roots.front();
            roots.pop();
            ret.push_back(src);
            
            for (const auto dest : adj_[src]) {
                assert(indegrees_[dest] > 0);
                if (--indegrees_[dest] == 0) roots.push(dest);
            }
        }
        
        return ret;
    }
    
    Graph build_prerequisite_graph(const int numCourses,
                                   const vector<pair<int, int>>& prerequisites)
    {
        Graph graph {numCourses};
        
        for (const auto prereq : prerequisites)
            graph.add_edge(prereq.second, prereq.first);
        
        return graph;
    }
}

vector<int> Solution::findOrder(const int numCourses,
                                const vector<pair<int, int>>& prerequisites)
{
    return build_prerequisite_graph(numCourses, prerequisites)
                .topological_sort();
}
