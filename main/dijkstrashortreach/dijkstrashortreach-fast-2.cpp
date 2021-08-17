#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cassert>
#include <cstdio>
#include <functional>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace {
    class Endpoints {
    public:
        Endpoints(unsigned u, unsigned v) noexcept;

        unsigned lower() const noexcept { return lower_; }
        unsigned upper() const noexcept { return upper_; }

    private:
        unsigned lower_, upper_;
    };

    Endpoints::Endpoints(const unsigned u, const unsigned v) noexcept
    {
        if (v < u) {
            lower_ = v;
            upper_ = u;
        } else {
            lower_ = u;
            upper_ = v;
        }
    }

    inline bool operator==(const Endpoints& lhs, const Endpoints& rhs) noexcept
    {
        return lhs.lower() == rhs.lower() && lhs.upper() == rhs.upper();
    }

    inline bool operator!=(const Endpoints& lhs, const Endpoints& rhs) noexcept
    {
        return !(lhs == rhs);
    }
}

namespace std {
    template<>
    struct hash<Endpoints> {
        inline size_t operator()(const Endpoints& endpoints) const noexcept;
    };

    size_t hash<Endpoints>::operator()(
            const Endpoints& endpoints) const noexcept
    {
        constexpr size_t p {17u}, q {31u}; // hashing primes
        return (p * q + endpoints.upper()) * q + endpoints.lower();
    }
}

namespace {
    using SparseMatrix = std::unordered_map<Endpoints, unsigned>;

    SparseMatrix read_distance_matrix(unsigned edge_count)
    {
        SparseMatrix distances;
        distances.max_load_factor(0.75f);

        while (edge_count--) {
            unsigned u {}, v {}, weight {};
            (void)std::scanf("%u%u%u", &u, &v, &weight);

            // Loops are always redundant and need not be recorded.
            if (u == v) continue;

            // We might have a parallel edge.
            const Endpoints key {u, v};
            const auto it = distances.find(key);

            // Use this edge if its weight is the lowest of any parallel edges.
            if (it == std::end(distances)) distances.emplace(key, weight);
            else if (it->second > weight) it->second = weight;
        }

        return distances;
    }

    struct OutEdge {
        // So that std::vector<OutEdge>::emplace_back(unsigned, unsigned) works.
        constexpr OutEdge(const unsigned dest, const unsigned weight) noexcept
                : dest{dest}, weight{weight} { }

        unsigned dest, weight;
    };

    using AdjacencyList = std::vector<std::vector<OutEdge>>;

    AdjacencyList build_adjacency_list(const unsigned vertex_count,
                                       const SparseMatrix& distances)
    {
        AdjacencyList adj (vertex_count);

        for (const auto& edge : distances) {
            const auto upper = edge.first.upper(), lower = edge.first.lower();
            const auto weight = edge.second;

            if (upper >= vertex_count)
                throw std::out_of_range{"vertex out of range"};

            // The graph is undirected.
            adj[lower].emplace_back(upper, weight);
            adj[upper].emplace_back(lower, weight);
        }

        return adj;
    }

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
                    // With the given constraints, this sum shouldn't overflow.
                    heap.insert_or_decrease(out_edge.dest,
                                            weight + out_edge.weight);
                }
            }
        }

        return lengths;
    }

    void display_signed(std::vector<unsigned> lengths,
                        const std::size_t skip) noexcept
    {
        static_assert(static_cast<int>(infinity) == -1,
                      "\"infinity\" won't be displayed as -1");

        const auto size = lengths.size();
        assert(size != 0u); // an exception would already have been thrown

        auto sep = "";
        for (std::size_t vertex {1u}; vertex != size; ++vertex) {
            if (vertex != skip) {
                // With the given constraints, only "infinity" should overflow.
                std::printf("%s%d", sep, static_cast<int>(lengths[vertex]));
                sep = " ";
            }
        }

        std::putchar('\n');
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        // Read how many vertices and edges the graph has.
        unsigned vertex_count {}, edge_count {};
        (void)std::scanf("%u%u", &vertex_count, &edge_count);
        ++vertex_count; // for 1-based indexing

        // Read the graph as an adjacency list, deduplicating parallel edges.
        const auto adj = build_adjacency_list(vertex_count,
                                              read_distance_matrix(edge_count));

        // Read the starting vertex and ensure it is in range.
        unsigned start {};
        (void)std::scanf("%u", &start);
        if (start == 0u || start >= vertex_count)
            throw std::out_of_range{"starting vertex is out of range"};

        // Find all shortest paths from that single starting vertex.
        const auto lengths = dijkstra(adj, start);

        // Display lengths of all shortest paths, except from start to itself.
        display_signed(lengths, start);
    }
}
