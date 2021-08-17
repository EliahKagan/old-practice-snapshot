namespace {
    class DisjointSets {
    public:
        explicit DisjointSets(const size_t size) : elems_(size, -1) { }

        // If i and j are in different sets, joins the sets and returns true.
        // If they are in the same set already, just returns false.
        bool unite(int i, int j) noexcept;

    private:
        int find(int i) noexcept;

        vector<int> elems_;
    };

    bool DisjointSets::unite(int i, int j) noexcept
    {
        // Find the ancestors and check if they're already the same.
        i = find(i);
        j = find(j);
        if (i == j) return false;

        // Union by rank.
        if (elems_[i] > elems_[j]) {
            // j has superior (more negative) rank.
            elems_[i] = j;
        } else {
            // If i and j have the same rank, promote i.
            if (elems_[i] == elems_[j]) --elems_[i];

            // i has superior (more negative) rank.
            elems_[j] = i;
        }

        return true;
    }

    int DisjointSets::find(int i) noexcept
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

class Solution {
public:
    static vector<int>
    findRedundantConnection(const vector<vector<int>>& edges);
};

vector<int> Solution::findRedundantConnection(const vector<vector<int>>& edges)
{
    DisjointSets sets {edges.size() + 1u}; // because we're not using vertex 0

    for (const auto& edge : edges)
        if (!sets.unite(edge.front(), edge.back())) return edge;

    return {};
}
