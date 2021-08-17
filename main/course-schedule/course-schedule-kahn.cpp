class Solution {
public:
    static bool canFinish(int num_courses,
                          const vector<pair<int, int>>& prerequisites);
};

namespace {
    class Graph {
    public:
        explicit Graph(int vertex_count);

        void add_edge(int src, int dest);

        bool has_cycle() &&; // cycle detection via Kahn's algorithm

    private:
        queue<int> get_roots() const;

        vector<vector<int>> adj_;
        vector<int> indegrees_;
    };

    inline Graph::Graph(const int vertex_count)
		: adj_(vertex_count), indegrees_(vertex_count)
    {
    }

    void Graph::add_edge(const int src, const int dest)
    {
        adj_[src].push_back(dest);
        ++indegrees_[dest];
    }

    bool Graph::has_cycle() &&
    {
        auto count = static_cast<int>(adj_.size());

        for (auto roots = get_roots(); !roots.empty(); roots.pop()) {
            --count;
            for (const auto dest : adj_[roots.front()])
                if (--indegrees_[dest] == 0) roots.push(dest);
        }

        assert(count >= 0);
        return count != 0;
    }

    queue<int> Graph::get_roots() const
    {
        queue<int> roots;

        for (auto src = 0; src != adj_.size(); ++src)
            if (indegrees_[src] == 0) roots.push(src);

        return roots;
    }

    Graph build_prerequisite_graph(const int num_courses,
                                   const vector<pair<int, int>>& prerequisites)
    {
        Graph graph {num_courses};

        for (const auto edge : prerequisites)
            graph.add_edge(edge.second, edge.first);

        return graph;
    }
}

bool Solution::canFinish(const int num_courses,
                         const vector<pair<int, int>>& prerequisites)
{
    return !build_prerequisite_graph(num_courses, prerequisites).has_cycle();
}
