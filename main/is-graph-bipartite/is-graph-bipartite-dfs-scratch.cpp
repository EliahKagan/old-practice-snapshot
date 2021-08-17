#include <algorithm>
#include <functional>
#include <vector>

using namespace std;

class Solution {
public:
    static bool isBipartite(const vector<vector<int>>& graph);
};

bool Solution::isBipartite(const vector<vector<int>>& graph)
{
    vector<int> vis (graph.size());
    
    const function<bool(int, int)> dfs = [&](const int src, const int color) {
        if (vis[src] != 0) return vis[src] == color;
        
        vis[src] = color;
        const auto& row = graph[src];
        
        return all_of(cbegin(row), cend(row), [&dfs, color](const int dest) {
            return dfs(dest, -color);
        });
    };
    
    for (auto start = 0; start != graph.size(); ++start)
        if (vis[start] == 0 && !dfs(start, 1)) return false;
    
    return true;
}
