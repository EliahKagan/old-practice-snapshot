#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cmath>
#include <cstdio>
#include <functional>
#include <limits>
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
        // So that std::vector<OutEdge>::emplace_back(unsigned, unsigned) works.
        constexpr OutEdge(const unsigned dest, const unsigned weight) noexcept
                : dest{dest}, weight{weight} { }

        unsigned dest, weight;
    };

    using AdjacencyList = std::vector<std::vector<OutEdge>>;

    class PrimHeap {
    public:
        explicit PrimHeap(std::size_t capacity);

        bool empty() const noexcept { return heap_.empty(); }

        const OutEdge& top() const noexcept { return heap_.front(); }

        void pop() noexcept;

        void insert_or_decrease(unsigned dest, unsigned weight) noexcept;

    private:
        static constexpr auto npos = std::numeric_limits<unsigned>::max();

        static constexpr bool order_ok(const OutEdge& parent_entry,
                                       const OutEdge& child_entry) noexcept;

        void sift_up(unsigned child) noexcept;

        void sift_down(unsigned parent) noexcept;

        inline unsigned pick_child(unsigned parent) const noexcept;

        inline void assign(unsigned index, const OutEdge& entry) noexcept;

        std::vector<unsigned> map_; // vertex -> index
        std::vector<OutEdge> heap_; // vertex -> cost
    };

    PrimHeap::PrimHeap(const std::size_t capacity)
            : map_(capacity, npos), heap_{}
    {
        heap_.reserve(capacity);
    }

    void PrimHeap::pop() noexcept
    {
        map_[top().dest] = npos;

        if (heap_.size() == 1u) {
            heap_.clear();
        } else {
            heap_.front() = heap_.back();
            heap_.pop_back();
            sift_down(0u);
        }
    }

    void PrimHeap::insert_or_decrease(const unsigned dest,
                                      const unsigned weight) noexcept
    {
        auto child = map_[dest];

        if (child == npos) { // insert
            map_[dest] = child = static_cast<unsigned>(heap_.size());
            heap_.emplace_back(dest, weight);
        }
        else if (weight < heap_[child].weight) { // decrease
            heap_[child].weight = weight;
        }
        else return; // do nothing

        sift_up(child);
    }

    constexpr unsigned PrimHeap::npos;

    constexpr bool PrimHeap::order_ok(const OutEdge& parent_entry,
                                      const OutEdge& child_entry) noexcept
    {
        return parent_entry.weight <= child_entry.weight;
    }

    void PrimHeap::sift_up(unsigned child) noexcept
    {
        const auto entry = heap_[child];

        while (child != 0u) {
            const auto parent = (child - 1u) / 2u;
            if (order_ok(heap_[parent], entry)) break;

            assign(child, heap_[parent]);
            child = parent;
        }

        assign(child, entry);
    }

    void PrimHeap::sift_down(unsigned parent) noexcept
    {
        const auto entry = heap_[parent];

        for (; ; ) {
            const auto child = pick_child(parent);
            if (child == npos || order_ok(entry, heap_[child])) break;

            assign(parent, heap_[child]);
            parent = child;
        }

        assign(parent, entry);
    }

    inline unsigned PrimHeap::pick_child(const unsigned parent) const noexcept
    {
        const auto left = parent * 2u + 1u;
        if (left >= heap_.size()) return npos;

        const auto right = left + 1u;
        return right == heap_.size() || order_ok(heap_[left], heap_[right])
                ? left
                : right;
    }

    inline void PrimHeap::assign(const unsigned index,
                                 const OutEdge& entry) noexcept
    {
        heap_[index] = entry;
        map_[entry.dest] = index;
    }

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

        PrimHeap heap {adj.size()};
        for (heap.insert_or_decrease(start, 0u); !heap.empty(); ) {
            const auto src = heap.top().dest, weight = heap.top().weight;
            heap.pop();

            lengths[src] = weight;

            for (const auto& out_edge : adj[src]) {
                if (lengths[out_edge.dest] == infinity) {
                    // Based on the problem constraints, sum shouldn't overflow.
                    heap.insert_or_decrease(out_edge.dest,
                                            weight + out_edge.weight);
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
