#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

namespace {
    struct OutEdge {
        // So that std::vector<OutEdge>::emplace_back(unsigned, unsigned) works.
        constexpr OutEdge(const unsigned dest, const unsigned weight) noexcept
                : dest{dest}, weight{weight} { }

        unsigned dest, weight;
    };

    using AdjacencyList = std::vector<std::vector<OutEdge>>;

    AdjacencyList read_graph()
    {
        unsigned vertex_count {}, edge_count {};
        std::cin >> vertex_count >> edge_count;
        ++vertex_count; // for 1-based indexing

        AdjacencyList adj (vertex_count);

        while (edge_count--) {
            unsigned u {}, v {}, weight {};
            std::cin >> u >> v >> weight;

            adj.at(u).emplace_back(v, weight);
            adj.at(v).emplace_back(u, weight); // undirected graph
        }

        return adj;
    }

    class PrimHeap {
    public:
        explicit PrimHeap(std::size_t capacity);

        bool empty() const noexcept { return heap_.empty(); }

        const OutEdge& top() const noexcept { return heap_.front(); }

        void pop() noexcept;

        void insert_or_decrease(const OutEdge& entry) noexcept;

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

    void PrimHeap::insert_or_decrease(const OutEdge& entry) noexcept
    {
        auto child = map_[entry.dest];

        if (child == npos) { // insert
            map_[entry.dest] = child = static_cast<unsigned>(heap_.size());
            heap_.push_back(entry);
        }
        else if (entry.weight < heap_[child].weight) { // decrease
            heap_[child].weight = entry.weight;
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

    unsigned prim_mst_total_weight(const AdjacencyList& adj,
                                   const unsigned start)
    {
        if (start >= adj.size())
            throw std::out_of_range{"invalid start vertex"};

        std::vector<bool> vis (adj.size());
        auto total_weight = 0u;

        PrimHeap heap {adj.size()};
        for (heap.insert_or_decrease({start, 0u}); !heap.empty(); ) {
            const auto cur = heap.top();
            heap.pop();

            vis[cur.dest] = true;
            total_weight += cur.weight;

            for (const auto& neighbor : adj[cur.dest])
                if (!vis[neighbor.dest]) heap.insert_or_decrease(neighbor);
        }

        return total_weight;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    const auto adj = read_graph();

    unsigned start {};
    std::cin >> start;

    std::cout << prim_mst_total_weight(adj, start) << '\n';
}
