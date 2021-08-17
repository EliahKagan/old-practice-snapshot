/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

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
    class DisjointSets {
    public:
        explicit DisjointSets(int size);

        // Joins sets containing i and j. Returns true iff they were separate.
        bool unite(int i, int j) noexcept;

    private:
        int find(int i) noexcept;

        std::vector<int> parents_, ranks_;
    };

    DisjointSets::DisjointSets(const int size) : parents_(size), ranks_(size)
    {
        iota(begin(parents_), end(parents_), 0u);
    }

    bool DisjointSets::unite(int i, int j) noexcept
    {
        // find the ancestors and stop if they are already the same
        i = find(i);
        j = find(j);
        if (i == j) return false;

        // union by rank
        if (ranks_[i] < ranks_[j]) {
            parents_[i] = j;
        } else {
            if (ranks_[i] == ranks_[j]) ++ranks_[i];
            parents_[j] = i;
        }

        return true;
    }

    int DisjointSets::find(int i) noexcept
    {
        // find the ancestor
        auto j = i;
        while (j != parents_[j]) j = parents_[j];

        // compress the path
        while (i != j) {
            const auto next = parents_[i];
            parents_[i] = j;
            i = next;
        }

        return j;
    }
}

/*You are required to complete this method*/
bool Graph::isCyclic()
{
    DisjointSets sets {V};

    for (auto v = 0; v != V; ++v) {
        for (const auto w : adj[v])
            if (v <= w && !sets.unite(v, w)) return true;
    }

    return false;
}
