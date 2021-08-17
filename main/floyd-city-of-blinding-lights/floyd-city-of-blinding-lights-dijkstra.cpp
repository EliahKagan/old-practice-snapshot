#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cmath>
#include <cstdio>
#include <functional>
#include <limits>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    struct UnweightedEdge {
        unsigned src, dest;
    };

    constexpr bool operator==(const UnweightedEdge& lhs,
                              const UnweightedEdge& rhs) noexcept
    {
        return lhs.src == rhs.src && lhs.dest == rhs.dest;
    }

    constexpr bool operator!=(const UnweightedEdge& lhs,
                              const UnweightedEdge& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

namespace std {
    template<>
    struct hash<UnweightedEdge> {
        constexpr size_t operator()(const UnweightedEdge&) const noexcept;
    };

    constexpr size_t hash<UnweightedEdge>::operator()(
            const UnweightedEdge& uwedge) const noexcept
    {
        constexpr size_t p {17u}, q {31u}; // hashing primes
        return (p * q + uwedge.src) * q + uwedge.dest;
    }
}

namespace {
    using SparseMatrix = std::unordered_map<UnweightedEdge, unsigned>;

    struct OutEdge {
        // So that std::vector<OutEdge>::emplace_back will work.
        constexpr OutEdge(const unsigned dest, const unsigned weight) noexcept
                : dest{dest}, weight{weight} { }

        unsigned dest, weight;
    };

    constexpr bool operator<(const OutEdge& lhs, const OutEdge& rhs) noexcept
    {
        return lhs.weight < rhs.weight;
    }

    constexpr bool operator>(const OutEdge& lhs, const OutEdge& rhs) noexcept
    {
        return lhs.weight > rhs.weight;
    }

    using AdjacencyList = std::vector<std::vector<OutEdge>>;

    template<typename T>
    using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

    constexpr auto infinity = std::numeric_limits<unsigned>::max();

    SparseMatrix read_distance_matrix(unsigned edge_count)
    {
        static constexpr auto target_load_factor = 0.75;
        const auto bucket_count = std::ceil(edge_count / target_load_factor);
        SparseMatrix distances (static_cast<std::size_t>(bucket_count));

        while (edge_count--) {
            unsigned src {}, dest {}, weight {};
            (void)std::scanf("%u%u%u", &src, &dest, &weight);
            if (src == dest) continue;

            // The problem description says that subsequently received parallel
            // edges replace previous ones, even if their weights are larger.
            distances[{src, dest}] = weight;
        }

        return distances;
    }

    AdjacencyList build_adjacency_list(const unsigned vertex_count,
                                       const SparseMatrix& distances)
    {
        AdjacencyList adj (vertex_count);

        for (const auto& edge : distances) {
            if (edge.first.src >= vertex_count
                    || edge.first.dest >= vertex_count)
                throw std::out_of_range{"vertex out of range"};

            adj[edge.first.src].emplace_back(edge.first.dest, edge.second);
        }

        return adj;
    }

    std::vector<unsigned> dijkstra(const AdjacencyList& adj,
                                   const unsigned start)
    {
        std::vector<unsigned> lengths (adj.size(), infinity);

        MinHeap<OutEdge> heap;
        for (heap.emplace(start, 0u); !heap.empty(); ) {
            const auto src = heap.top().dest, length = heap.top().weight;
            heap.pop();
            if (lengths[src] != infinity) continue;

            lengths[src] = length;

            for (const auto& out_edge : adj[src]) {
                if (lengths[out_edge.dest] == infinity) {
                    // Shouldn't overflow, based on the problem constraints.
                    heap.emplace(out_edge.dest, length + out_edge.weight);
                }
            }
        }

        return lengths;
    }

    void run_queries(const AdjacencyList& adj, int query_count)
    {
        std::vector<std::vector<unsigned>> memo (adj.size());

        while (query_count-- > 0) {
            unsigned src {}, dest {};
            (void)std::scanf("%u%u", &src, &dest);

            auto& lengths = memo.at(src);
            if (lengths.empty()) lengths = dijkstra(adj, src);
            const auto length = lengths.at(dest);

            if (length == infinity) std::puts("-1");
            else std::printf("%u\n", length);
        }
    }
}

int main()
{
    unsigned vertex_count {}, edge_count {};
    (void)std::scanf("%u%u", &vertex_count, &edge_count);
    ++vertex_count; // for 1-based indexing

    const auto adj = build_adjacency_list(vertex_count,
                                          read_distance_matrix(edge_count));

    int query_count {};
    (void)std::scanf("%d", &query_count);

    run_queries(adj, query_count);
}
