#include <iterator>
#include <utility>
#include <vector>

using namespace std;

class Solution {
public:
    static vector<int>
    findOrder(int numCourses,
              const vector<pair<int, int>>& prerequisites) noexcept;
};

namespace {
    class Graph {
    public:
        explicit Graph(int vertex_count) noexcept;

        void add_edge(int src, int dest) noexcept;

        vector<int> topological_sort() && noexcept; // empty if cyclic

    private:
        template<typename It>
        It get_roots(It p) const noexcept;

        vector<vector<int>> adj_;
        vector<int> indegrees_;
    };

    Graph::Graph(const int vertex_count) noexcept
        : adj_(vertex_count), indegrees_(vertex_count)
    {
    }

    inline void Graph::add_edge(const int src, const int dest) noexcept
    {
        adj_[src].push_back(dest);
        ++indegrees_[dest];
    }

    vector<int> Graph::topological_sort() && noexcept
    {
        vector<int> ret (adj_.size());
        auto left = begin(ret);
        auto right = get_roots(left);

        for (; left != right; ++left) {
            for (const auto dest : adj_[*left]) {
                if (--indegrees_[dest] != 0) continue;

                *right = dest;
                ++right;
            }
        }

        if (right != end(ret)) ret.clear();
        return ret;
    }

    template<typename It>
    It Graph::get_roots(It d_first) const noexcept
    {
        const auto n = static_cast<int>(adj_.size());

        for (auto i = 0; i != n; ++i) {
            if (indegrees_[i] == 0) {
                *d_first = i;
                ++d_first;
            }
        }

        return d_first;
    }

    Graph make_graph(const int vertex_count,
                     const vector<pair<int, int>>& reverse_edges) noexcept
    {
        Graph graph {vertex_count};

        for (const auto& redge : reverse_edges)
            graph.add_edge(redge.second, redge.first);

        return graph;
    }
}

vector<int>
Solution::findOrder(int numCourses,
                    const vector<pair<int, int>>& prerequisites) noexcept
{
    return make_graph(numCourses, prerequisites).topological_sort();
}
