namespace {
    struct Element {
        unsigned parent;
        unsigned rank;
    };
}

class Solution {
public:
    int findCircleNum(vector<vector<int>>& matrix) {
        // record the size of the adjacency matrix, for convenience
        const auto n = static_cast<unsigned>(matrix.size());
        if (n == 0u) return 0;

        // create and initialize that many singleton sets
        vector<Element> elems (n);
        for (auto i = 0u; i != n; ++i) {
            elems[i].parent = i;
            elems[i].rank = 0u;
        }

        // finds the representative element, performing full path compression
        const auto findSet = [n, &elems](unsigned i) {
            auto j = i;
            while (j != elems[j].parent) j = elems[j].parent;

            while (i != j) { // path compression
                const auto p = elems[i].parent;
                elems[i].parent = j;
                i = p;
            }

            return j;
        };

        // union by rank
        const auto unite = [n, &elems, &findSet](unsigned i, unsigned j) {
            i = findSet(i);
            j = findSet(j);

            if (elems[i].rank < elems[j].rank) {
                elems[i].parent = j;
            } else {
                if (elems[i].rank == elems[j].rank) ++elems[i].rank;
                elems[j].parent = i;
            }
        };

        // perform unions according to the adjacency matrix
        for (auto i = 0u; i != n - 1u; ++i) {
            for (auto j = i + 1u; j != n; ++j)
                if (matrix[i][j]) unite(i, j);
        }

        // count the number of distinct sets (i.e., number of representatives)
        auto count = 0;
        for (auto i = 0u; i != n; ++i)
            if (elems[i].parent == i) ++count;

        return count;
    }
};
