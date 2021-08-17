/*The structure of the class is as follows 
which contains an integer V denoting the no 
of vertices and a list of adjacency vertices.
class Graph
{
    int V;
    list<int> *adj;
public :
    Graph(int V);
    void addEdge(int v,int w);
    bool isCyclic();
};*/

namespace {
    // Helper function for isCyclic(). For each node prev in a separate
    // connected component, and each of its children cur, run this once.
    bool dfs(const int prev, const int cur, const list<int> *const adj,
             vector<bool>& vis) // returns true if a cycle is detected
    {
        if (vis[cur]) return true;
        
        vis[cur] = true;
        for (const auto next : adj[cur])
            if (next != prev && dfs(cur, next, adj, vis)) return true;
        
        return false;
    }
}

// Naive cycle-detection algorithm. When we get to a node that has already
// been visited, other than the previously visited node, we know there is
// a cycle. Otherwise, there is no cycle. (Most of the work is done in the
// dfs() helper function.)
bool Graph :: isCyclic()
{
    vector<bool> vis (V);
    
    for (auto cur = 0; cur != V; ++cur) {
        if (vis[cur]) continue;
        
        for (const auto next : adj[cur])
            if (dfs(cur, next, adj, vis)) return true;
    }
    
    return false;
}
