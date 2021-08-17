/*
Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function would be added by GfG's Online Judge.*/


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
}

/*You are required to complete this method*/
bool Graph::isCyclic()
{
    DisjointSets sets {V};
    auto redundancy = 0;

    for (auto v = 0; v != V; ++v) {
        for (const auto w : adj[v]) {
            if (v == w) return true;

            if (sets.unite(v, w))   --redundancy;
            else                    ++redundancy;
        }
    }

    assert(redundancy >= 0);
    return redundancy != 0;
}
