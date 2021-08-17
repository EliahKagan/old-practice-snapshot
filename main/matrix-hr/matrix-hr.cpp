#ifdef NDEBUG
#error Assertions unexpectedly disabled.
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

namespace {
    // Disjoint-set-union data structure where each component is inactive
    // (uninfected) or active (infected). The union of components is active
    // when either was already active. The purpose of this data structure is to
    // detect each time two already-active components are united.
    class DisjointSets {
    public:
        explicit DisjointSets(int count);

        // Marks the specified element as an active vertex.
        void activate(int vertex) noexcept;

        // Union by rank. Returns true iff separate active sets were joined.
        bool unite(int vertex1, int vertex2) noexcept;
    
    private:
        enum class State : bool { inactive, active };

        static std::size_t convert_count(int count) noexcept;

        explicit DisjointSets(std::size_t count);

        int count() const noexcept;

        bool exists(int vertex) const noexcept;

        // Finds the representative element, performing full path compression.
        int find_set(int vertex) noexcept;

        // Joins the child to the parent. Returns true iff both were active.
        bool join(int parent, int child) noexcept;

        std::vector<int> parents_;
        std::vector<int> ranks_;
        std::vector<State> states_;
    };

    inline std::size_t DisjointSets::convert_count(int count) noexcept
    {
        assert(0 <= count);
        return static_cast<std::size_t>(count);
    }

    DisjointSets::DisjointSets(const std::size_t count)
        : parents_(count), ranks_(count), states_(count)
    {
        std::iota(begin(parents_), end(parents_), 0);
    }

    DisjointSets::DisjointSets(const int count)
        : DisjointSets{convert_count(count)}
    {
    }

    inline int DisjointSets::count() const noexcept
    {
        return static_cast<int>(parents_.size());
    }

    inline bool DisjointSets::exists(const int vertex) const noexcept
    {
        return 0 <= vertex && vertex < count();
    }

    inline void DisjointSets::activate(const int vertex) noexcept
    {
        assert(exists(vertex));
        states_[vertex] = State::active;
    }

    bool DisjointSets::unite(int vertex1, int vertex2) noexcept
    {
        assert(exists(vertex1));
        assert(exists(vertex2));

        // Find the ancestors and stop of they are already the same.
        vertex1 = find_set(vertex1);
        vertex2 = find_set(vertex2);
        if (vertex1 == vertex2) return false;

        // Union by rank.
        if (ranks_[vertex1] < ranks_[vertex2]) return join(vertex2, vertex1);
        if (ranks_[vertex1] == ranks_[vertex2]) ++ranks_[vertex1];
        return join(vertex1, vertex2);
    }

    int DisjointSets::find_set(int vertex) noexcept
    {
        // Find the ancestor.
        auto leader = vertex;
        while (leader != parents_[leader]) leader = parents_[leader];

        // Compress the path.
        while (vertex != leader) {
            const auto parent = parents_[vertex];
            parents_[vertex] = leader;
            vertex = parent;
        }

        return leader;
    }

    bool DisjointSets::join(const int parent, const int child) noexcept
    {
        parents_[child] = parent;

        if (states_[child] == State::active) {
            if (states_[parent] == State::active) return true;
            states_[parent] = State::active;
        }

        return false;
    }

    // An edge in an weighted undirected graph. Edges compare by their weights.
    struct Edge {
        int vertex1;
        int vertex2;
        long long weight;
    };

    constexpr bool operator<(const Edge& lhs, const Edge& rhs) noexcept
    {
        return lhs.weight < rhs.weight;
    }

    constexpr bool operator>(const Edge& lhs, const Edge& rhs) noexcept
    {
        return lhs.weight > rhs.weight;
    }

    inline std::istream& operator>>(std::istream& is, Edge& edge)
    {
        return is >> edge.vertex1 >> edge.vertex2 >> edge.weight;
    }

    std::vector<Edge> read_edges_sorted(const int edge_count)
    {
        std::vector<Edge> edges (static_cast<std::size_t>(edge_count));

        std::copy_n(std::istream_iterator<Edge>{std::cin},
                    edge_count, begin(edges));
        
        std::sort(begin(edges), end(edges), std::greater<>{});
        return edges;
    }

    DisjointSets read_vertices(const int count, int active_count)
    {
        DisjointSets sets {count};

        while (active_count-- > 0) {
            int vertex {};
            std::cin >> vertex;
            assert(std::cin);
            sets.activate(vertex);
        }

        return sets;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    int city_count {}, machine_count {};
    std::cin >> city_count >> machine_count;
    
    assert(0 < city_count);
    assert(0 <= machine_count);
    assert(machine_count <= city_count);

    const auto edges = read_edges_sorted(city_count - 1);
    auto sets = read_vertices(city_count, machine_count);
    auto total_bridge_weight = 0LL;
    auto bridge_count = 0; // for error checking and debugging

    for (const auto& edge : edges) {
        if (sets.unite(edge.vertex1, edge.vertex2)) {
            total_bridge_weight += edge.weight;
            ++bridge_count;
        }
    }
    
    assert(bridge_count == machine_count - 1);
    std::cout << total_bridge_weight << '\n';
}
