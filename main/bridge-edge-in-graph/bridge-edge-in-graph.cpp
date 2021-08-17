/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


// your task is to complete this function
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
    bool isBridge();
};*/

namespace {
    class DisjointSets {
    public:
        explicit DisjointSets(int count);

        // If i and j are in separate sets, unites them and returns true.
        // If i and j are already in the same set, returns false.
        bool unite(int i, int j) noexcept;

    private:
        int findSet(int i) noexcept;

        vector<int> elems_;
    };

    DisjointSets::DisjointSets(const int count) : elems_(count, -1) { }

    bool DisjointSets::unite(int i, int j) noexcept
    {
        i = findSet(i);
        j = findSet(j);
        if (i == j) return false;

        // union by rank
        if (elems_[i] < elems_[j]) {
            // i has higher (more negative) rank
            elems_[j] = i;
        } else {
            if (elems_[i] == elems_[j]) {
                // they have the same rank, so promote j to the next rank
                --elems_[j];
            }

            // j has higher (more negative) rank
            elems_[i] = j;
        }

        return true;
    }

    int DisjointSets::findSet(int i) noexcept
    {
        // Find the ancestor.
        auto j = i;
        while (elems_[j] >= 0) j = elems_[j];

        // Compress the path.
        while (i != j) {
            const auto p = elems_[i];
            elems_[i] = j;
            i = p;
        }

        return j;
    }

    // Connects i to j iff i < j and the row for i in the adjacency list has j.
    void connectHigherNeighbors(DisjointSets& sets, const list<int>* const adj,
                                                    const int i)
    {
        for (const auto j : adj[i])
            if (i < j) sets.unite(i, j);
    }

    // Connects i to j iff i < j and j != v and the row for j in the adjacency
    // list has i. Returns true if the edge i => v was found, false otherwise.
    bool connectHigherNeighborsExcept(DisjointSets& sets,
            const list<int>* const adj, const int i, const int v)
    {
        auto found = false;

        for (const auto j : adj[i]) {
            if (i < j)  {
                if (j == v) found = true;
                else sets.unite(i, j);
            }
        }

        return found;
    }
}

bool Graph::isBridge(int u, int v)
{
    assert(0 <= u && u < V && 0 <= v && v < V);

    // Loops don't affect connectivity.
    if (u == v) return false;

    // The graph is undirected, so without loss of generality, u < v.
    if (u > v) swap(u, v);

    // Track connectivity *except* that which is induced by u => v.
    // Then if u => v was found, see if adding it affects connectivity.
    DisjointSets sets {V};
    for (auto i = 0; i < u; ++i) connectHigherNeighbors(sets, adj, i);
    for (auto i = u + 1; i < V; ++i) connectHigherNeighbors(sets, adj, i);
    return connectHigherNeighborsExcept(sets, adj, u, v) && sets.unite(u, v);
}
