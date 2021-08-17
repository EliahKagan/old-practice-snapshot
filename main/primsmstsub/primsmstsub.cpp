#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    using std::size_t;

    // A modified binary minheap, suitable for Prim's algorithm.
    // Traditionally one adds contains() and decrease() methods. I have done
    // this but also omitted push(), which Prim's algorithm doesn't need.
    template<typename Key, typename Value>
    class PrimHeap {
    public:
        struct Entry {
            Key key;
            Value value;
        };

        // Constructs a new heap with sequential keys in [min_key, max_key].
        // Each key initially maps to the specified value, which defaults to
        // the maximum value of the type (for "infinity").
        explicit PrimHeap(Key min_key, Key max_key,
                          Value value = std::numeric_limits<Value>::max());

        const Entry& top() const { return elems_.at(0u); }

        bool empty() const noexcept { return elems_.empty(); }

        size_t size() const noexcept { return elems_.size(); }

        void pop();

        bool contains(const Key key) const noexcept
        {
            return table_.count(key) != 0;
        }

        void decrease(Key key, Value value);

    private:
        static constexpr auto npos = std::numeric_limits<size_t>::max();

        void sift_up(size_t child);

        void sift_down(size_t parent);

        size_t pick_child(size_t parent) const noexcept;

        void exchange(size_t src, size_t dest);

        void record(const size_t src) { table_[elems_[src].key] = src; }

        bool order_ok(size_t parent, size_t child) const noexcept
        {
            return elems_[parent].value <= elems_[child].value;
        }

        std::unordered_map<Key, size_t> table_;
        std::vector<Entry> elems_;
    };

    template<typename Key, typename Value>
    PrimHeap<Key, Value>::PrimHeap(Key min_key, const Key max_key,
                                   const Value value)
        : table_{}, elems_(static_cast<size_t>(max_key - min_key) + 1u)
    {
        const auto len = elems_.size();
        
        for (size_t i {0u}; i != len; ++i) {
            auto& ent = elems_[i];
            ent.key = min_key++;
            ent.value = value;
            table_.emplace(ent.key, i);
        }

        assert(min_key == max_key + static_cast<Key>(1));
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::pop()
    {
        const auto key = top().key;

        if (size() == 1u) {
            table_.clear();
            elems_.clear();
        } else {
            table_.erase(key);
            elems_.front() = elems_.back();
            elems_.pop_back();
            sift_down(0u);
        }
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::decrease(const Key key, const Value value)
    {
        const auto child = table_.at(key);
        auto& ent = elems_[child];

        if (value < ent.value) {
            ent.value = value;
            sift_up(child);
        }
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::sift_up(size_t child)
    {
        while (child != 0u) {
            const auto parent = (child - 1u) / 2u;
            if (order_ok(parent, child)) break;

            exchange(child, parent);
            child = parent;
        }

        record(child);
    }

    template<typename Key, typename Value>
    void PrimHeap<Key, Value>::sift_down(size_t parent)
    {
        for (; ; ) {
            const auto child = pick_child(parent);
            if (child == npos || order_ok(parent, child)) break;

            exchange(parent, child);
            parent = child;
        }

        record(parent);
    }

    template<typename Key, typename Value>
    size_t PrimHeap<Key, Value>::pick_child(const size_t parent) const noexcept
    {
        const auto left = parent * 2u + 1u;
        if (left >= size()) return npos;

        const auto right = left + 1u;
        return right == size() || order_ok(left, right) ? left : right;
    }

    template<typename Key, typename Value>
    inline void PrimHeap<Key, Value>::exchange(const size_t src,
                                               const size_t dest)
    {
        using std::swap;
        swap(elems_[dest], elems_[src]);
        record(src);
    }

    template<typename Vertex, typename Weight>
    struct Edge {
        Edge(const Vertex vertex, const Weight weight) noexcept
            : vertex{vertex}, weight{weight} { }

        Vertex vertex;
        Weight weight;
    };

    // An adjacency list representation of a weighted undirected graph.
    template<typename Vertex, typename Weight>
    using Graph = std::vector<std::vector<Edge<Vertex, Weight>>>;

    template<typename Vertex, typename Weight>
    inline void add_edge(Graph<Vertex, Weight>& adj,
                         const Vertex u, const Vertex v, const Weight wt)
    {
        static constexpr Weight zero {0};
        if (wt < zero)
            throw std::domain_error{"negative edge weights not allowed"};

        adj.at(u).emplace_back(v, wt);
        adj.at(v).emplace_back(u, wt);
    }

    constexpr size_t k_first_vertex {1u}; // lowest-numbered vertex used

    Graph<size_t, int> read_graph()
    {
        // read the order (vertex count) and edge count for the graph
        size_t vertex_count {};
        int edge_count {};
        std::cin >> vertex_count >> edge_count;
        if (edge_count < 0) throw std::domain_error{"negative edge count?"};

        // create an adjacency list with the correct number of (empty) rows
        Graph<size_t, int> adj (k_first_vertex + vertex_count);

        // read edge information and populate the adjacency list accordingly
        while (edge_count-- != 0u) {
            size_t u {}, v {};
            int wt {};
            std::cin >> u >> v >> wt;

            add_edge(adj, u, v, wt);
        }

        return adj;
    }

    // Calculates a connected graph's MST's weight sum via Prim's algorithm.
    int compute_total_weight(const Graph<size_t, int>& adj, const size_t start)
    {
        auto total_cost = 0;

        PrimHeap<size_t, int> cost_heap {k_first_vertex, adj.size() - 1u};
        cost_heap.decrease(start, 0);

        while (!cost_heap.empty()) {
            const auto ent = cost_heap.top();
            cost_heap.pop();

            total_cost += ent.value;

            for (const auto& edge : adj[ent.key]) {
                if (cost_heap.contains(edge.vertex))
                    cost_heap.decrease(edge.vertex, edge.weight);
            }
        }

        return total_cost;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    const auto adj = read_graph();
    size_t start {};
    std::cin >> start;

    std::cout << compute_total_weight(adj, start) << '\n';
}
