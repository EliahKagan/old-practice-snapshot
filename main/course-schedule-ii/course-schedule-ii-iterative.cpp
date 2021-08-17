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

    struct Frame {
        int vertex; // the current vertex
        int index;  // index into its row in the adjacency list
    };

    // Performs reverse topological sort by depth-first traversal.
    // When the graph is cyclic, returns an empty vector.
    vector<int> reverse_topological_sort(const vector<vector<int>>& adj)
    {
        vector<int> out;
        out.reserve(adj.size());

        vector<Color> vis (adj.size());
        stack<Frame> frames; // reusing the stack to fewer memory allocations

        // Tells if a directed graph has a cycle. For as long as no cycle is
        // found, also builds a reverse topological sort as it retreats.
        const auto has_cycle_from = [&](const int start) {
            if (vis[start] == Color::black) return false;

            assert(vis[start] != Color::gray);
            vis[start] = Color::gray;
            assert(frames.empty());
            frames.push({start, 0});

            while (!frames.empty()) {
                auto& frame = frames.top();
                const auto& row = adj[frame.vertex];

                if (frame.index == row.size()) { // retreat
                    out.push_back(frame.vertex);
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

                case Color::gray: // cycle found
                    return true;

                case Color::black: // already explored, don't revisit
                    break;
                }
            }

            return false;
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
