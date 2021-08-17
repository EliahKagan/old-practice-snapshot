class Solution {
public:
    static bool isBipartite(const vector<vector<int>>& graph);
};

namespace {
    enum class Color {
        white,  // not visited, and thus not assigned a color
        red,    // colored as the first of two parts of the graph
        blue    // colored as the second of two parts of the graph
    };

    inline Color nextColor(const Color color)
    {
        switch (color) {
        case Color::white:
            throw invalid_argument{"color mustn't be clear"};
        case Color::red:
            return Color::blue;
        case Color::blue:
            return Color::red;
        }

        throw invalid_argument{"unrecognized color value"};
    }

    bool componentIsBipartite(const vector<vector<int>>& graph,
                              vector<Color>& vis, int src)
    {
        queue<int> q;
        q.push(src);

        for (auto color = nextColor(vis[src]); !q.empty(); color = nextColor(color)) {
            for (auto breadth = q.size(); breadth; --breadth) {
                src = q.front();
                q.pop();

                for (const auto dest : graph[src]) {
                    if (vis[dest] == color) continue;

                    if (vis[dest] != Color::white) return false;

                    vis[dest] = color;
                    q.push(dest);
                }
            }
        }

        return true;
    }
}

bool Solution::isBipartite(const vector<vector<int>>& graph)
{
    vector<Color> vis (graph.size(), Color::white);

    for (auto i = 0; i != graph.size(); ++i) {
        if (vis[i] != Color::white) continue;

        vis[i] = Color::red;
        if (!componentIsBipartite(graph, vis, i)) return false;
    }

    return true;
}
