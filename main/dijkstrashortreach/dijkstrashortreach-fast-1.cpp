#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#ifdef __MINGW32__
#define __USE_MINGW_ANSI_STDIO 1
#endif

#include <cassert>
#include <cstdio>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <vector>

namespace {
    using std::size_t;

    // A modified binary minheap, suitable for Prim's or Dijkstra's algorithms.
    // Traditionally one adds contains() and decrease() methods. I have done
    // this but also omitted push(), which those algorithms don't need.
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
        PrimHeap(Key min_key, Key max_key,
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

    // An element of a row of an adjacency list of a weighted undirected graph.
    template<typename Vertex, typename Weight>
    struct Neighbor {
        Neighbor(const Vertex vertex, const Weight weight) noexcept
            : dest{vertex}, wt{weight} { }

        Vertex dest;
        Weight wt;
    };

    // An adjacency list representation of a weighted undirected graph.
    template<typename Vertex, typename Weight>
    using Graph = std::vector<std::vector<Neighbor<Vertex, Weight>>>;

    // A pair of vertices signifying an undirected edge of unspecified weight.
    template<typename Vertex>
    class Endpoints {
    public:
        Endpoints(const Vertex u, const Vertex v) noexcept
        {
            if (u > v) {
                u_ = v;
                v_ = u;
            } else {
                u_ = u;
                v_ = v;
            }
        }

        constexpr Vertex u() const noexcept { return u_; }

        constexpr Vertex v() const noexcept { return v_; }

    private:
        Vertex u_, v_;
    };

    template<typename Vertex>
    constexpr bool operator==(const Endpoints<Vertex>& lhs,
                              const Endpoints<Vertex>& rhs) noexcept
    {
        return lhs.u() == rhs.u() && lhs.v() == rhs.v();
    }

    template<typename Vertex>
    constexpr bool operator!=(const Endpoints<Vertex>& lhs,
                              const Endpoints<Vertex>& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    constexpr size_t k_hash_seed {17u}, k_hash_multiplier {31u};
}

namespace std {
    template<typename Vertex>
    struct hash<Endpoints<Vertex>> {
        constexpr size_t operator()(const Endpoints<Vertex>& uv)
                const noexcept;
    };

    template<typename Vertex>
    constexpr size_t hash<Endpoints<Vertex>>::operator()(
            const Endpoints<Vertex>& uv) const noexcept
    {
        //return (k_hash_seed * k_hash_multiplier + uv.u())
        //        * k_hash_multiplier + uv.v();
        size_t ret {2166136261u};
        ret = (ret * 16777619u) ^ uv.u();
        ret = (ret * 16777619u) ^ uv.v();
        return ret;
    }
}

namespace {
    constexpr size_t k_first_vertex {1u}; // lowest-numbered vertex used

    // Reads a graph as a compact adjacency matrix consisting of an unordered
    // map from endpoint pairs of type Endpoint<size_t> weights of type int.
    std::unordered_map<Endpoints<size_t>, int>
    read_simple_graph_edges(int edge_count)
    {
        if (edge_count < 0)
            throw std::invalid_argument{"can't read negatively many edges"};

        std::unordered_map<Endpoints<size_t>, int> edges;

        while (edge_count-- != 0) {
            size_t u {}, v {};
            int wt {};
            (void)std::scanf("%zu%zu%d", &u, &v, &wt);
            if (wt <= 0) throw std::domain_error{"weights must be positive"};

            if (u == v) continue;

            auto& acc = edges[{u, v}];
            if (acc == 0 || wt < acc) acc = wt;
        }

        return edges;
    }

    // Reads a graph as [order, size], [u1, v1, wt1], [u2, v2, wt2], ...
    Graph<size_t, int> read_graph()
    {
        // read the order (vertex count) and edge count for the graph
        size_t vertex_count {};
        int edge_count {};
        (void)std::scanf("%zu%d", &vertex_count, &edge_count);

        // create an adjacency list with the correct number of (empty) rows
        Graph<size_t, int> adj (k_first_vertex + vertex_count);

        for (const auto& edge : read_simple_graph_edges(edge_count)) {
            // edge is (first: (u_, v_),  second: wt)
            adj.at(edge.first.u()).emplace_back(edge.first.v(), edge.second);
            adj.at(edge.first.v()).emplace_back(edge.first.u(), edge.second);
        }

        return adj;
    }

    // Calculates all the shortest reaches in a graph from a given start
    // vertex, using Dijkstra's algorithm.
    std::vector<int> compute_shortest_reaches(const Graph<size_t, int>& adj,
                                              const size_t start,
                                              const int unreachable_cost)
    {
        std::vector<int> costs (adj.size(), unreachable_cost);
        costs.at(start) = 0;

        PrimHeap<size_t, int> cost_heap {k_first_vertex, adj.size() - 1u};
        cost_heap.decrease(start, 0);

        while (!cost_heap.empty()) {
            const auto ent = cost_heap.top();
            cost_heap.pop();
            if (ent.value == std::numeric_limits<int>::max()) break;
            costs[ent.key] = ent.value;

            for (const auto& neighbor : adj[ent.key]) {
                if (cost_heap.contains(neighbor.dest))
                    cost_heap.decrease(neighbor.dest, ent.value + neighbor.wt);
            }
        }

        return costs;
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        const auto adj = read_graph();
        size_t start {};
        (void)std::scanf("%zu", &start);

        const auto costs = compute_shortest_reaches(adj, start, -1);
        const auto len = costs.size();

        auto sep = "";
        for (auto i = k_first_vertex; i != len; ++i) {
            if (i != start) {
                std::printf("%s%d", sep, costs[i]);
                sep = " ";
            }
        }
        std::putchar('\n');
    }
}
