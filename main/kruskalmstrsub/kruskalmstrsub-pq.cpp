#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

namespace {
    using std::size_t;

    class DisjointSets {
    public:
        explicit DisjointSets(size_t size);

        // Joins sets containing i and j. Returns true iff they were separate.
        bool unite(unsigned i, unsigned j) noexcept;

    private:
        unsigned find(unsigned i) noexcept;

        std::vector<unsigned> parents_, ranks_;
    };

    DisjointSets::DisjointSets(const size_t size)
        : parents_(size), ranks_(size)
    {
        std::iota(std::begin(parents_), std::end(parents_), 0u);
    }

    bool DisjointSets::unite(unsigned i, unsigned j) noexcept
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

    unsigned DisjointSets::find(unsigned i) noexcept
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

    struct Edge {
        unsigned u, v;
        int wt;
    };

    inline std::istream& operator>>(std::istream& in, Edge& edge)
    {
        return in >> edge.u >> edge.v >> edge.wt;
    }

    std::vector<Edge> read_edges(const size_t edge_count)
    {
        std::vector<Edge> edges (edge_count);
        for (auto& edge : edges) std::cin >> edge;
        return edges;
    }

    int compute_mst_weight(size_t vertex_count, std::vector<Edge>&& edges)
    {
        if (vertex_count < 2u) return 0;

        // Add 1 because we are not using vertex 0 (we want 1-based indexing).
        DisjointSets sets {vertex_count + 1u};

        // Just sort edges by weight, as all MSTs have the same total weight.
        const auto gt = [](const Edge& lhs, const Edge& rhs) noexcept {
            return lhs.wt > rhs.wt;
        };
        
        // This may save time because we only pop edges until we have an MST.
        using PQ = std::priority_queue<Edge, std::vector<Edge>, decltype(gt)>;
        PQ heap {gt, std::move(edges)};

        // Pick up edges until we have an MST or all edges were considered.
        auto weight = 0;
        for (auto needed = vertex_count - 1u; needed != 0u && !heap.empty();
                                              heap.pop()) {
            const auto& edge = heap.top();

            if (sets.unite(edge.u, edge.v)) {
                weight += edge.wt;
                --needed;
            }
        }

        return weight;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t vertex_count {}, edge_count {};
    std::cin >> vertex_count >> edge_count;

    std::cout << compute_mst_weight(vertex_count, read_edges(edge_count))
              << '\n';
}
