#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    class DisjointSets {
    public:
        // Creates count non-overlapping sets, each containing one element.
        explicit DisjointSets(int count);

        // Joins the set containing i with the set containing j. Returns false
        // if they were already in the same set. Returns true if they were not.
        bool unite(int i, int j) noexcept;

    private:
        // Finds the representative element for the set that contains i.
        int find(int i) noexcept;

        std::vector<int> elems_;
    };

    DisjointSets::DisjointSets(const int count) : elems_(count, -1) { }

    bool DisjointSets::unite(int i, int j) noexcept
    {
        // Find the ancestors and check if they're already the same.
        i = find(i);
        j = find(j);
        if (i == j) return false;

        // Union by rank.
        if (elems_[i] > elems_[j]) {
            elems_[i] = j; // j has superior (more negative) rank
        } else {
            // if i and j have equal rank, then promote i
            if (elems_[i] == elems_[j]) --elems_[i];

            elems_[j] = i; // i has superior (more negative) rank
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

    struct Edge {
        int x, y, r;
    };
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto v = 0, e = 0;
    std::cin >> v >> e;

    std::vector<Edge> edges (e);
    for (auto& edge : edges) std::cin >> edge.x >> edge.y >> edge.r;

    std::sort(std::begin(edges), std::end(edges),
              [](const Edge& lhs, const Edge& rhs) noexcept {
        // Each MST has the same weight sum so we don't need the "special" one.
        return lhs.r < rhs.r;
    });

    DisjointSets sets {v + 1}; // because we're not using 0
    
    auto sum = 0;
    for (const auto& edge : edges)
        if (sets.unite(edge.x, edge.y)) sum += edge.r;

    std::cout << sum << '\n';
}
