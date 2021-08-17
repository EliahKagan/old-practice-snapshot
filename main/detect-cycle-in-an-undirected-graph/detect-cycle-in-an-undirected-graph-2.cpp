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
    // Helper function for isCyclic(). Returns the number of edges in the
    // connected component containing cur, assuming each adjacency list entry
    // is one edge. For an undirected graph, this value must be divided by 2.
    int dfsCountEdges(const int cur, const list<int> *const adj,
                      vector<bool>& vis)
    {
        if (vis[cur]) return 0;
        vis[cur] = true;
        
        auto count = 0;
        for (const auto next : adj[cur])
            count += 1 + dfsCountEdges(next, adj, vis);
        
        return count;
    }
    
    // Helper function for isCyclic(). Returns the number of edges in an
    // the connected component of an undirected graph containing cur.
    inline int dfsCountEdgesUndirected(
            const int cur, const list<int> *const adj, vector<bool>& vis)
    {
        const auto count = dfsCountEdges(cur, adj, vis);
        assert(count % 2 == 0);
        return count / 2;
    }
}

// A graph is either cyclic or a minimal spanning forest, so checking if it's
// a MSF is sufficient. A graph is an MSF if and only if its number of edges is
//
//          (number of nodes) - (number of [connected] components),
//
// becuase only way to add an edge while preserving minimality is to connect
// two components (decrementing the number of components); the only way to
// remove an edge is to disconnect a component (incrementing the number) of
// components; and when the MSF has a single component (i.e., is a MST), its
// edge count is (number of nodes) - 1.
bool Graph::isCyclic()
{
    auto edges = 0, components = 0;
    
    vector<bool> vis (V);
    for (auto cur = 0; cur != V; ++cur) {
        if (!vis[cur]) {
            edges += dfsCountEdgesUndirected(cur, adj, vis);
            ++components;
        }
    }
    
    assert(edges + components >= V);
    return edges + components != V;
}
