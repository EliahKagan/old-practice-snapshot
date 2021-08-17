#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
    template<typename ContextuallyConvertibleToBool>
    inline void ensure(const ContextuallyConvertibleToBool& condition) noexcept
    {
        if (condition) return;
        std::abort();
    }

    // An edge in a directed graph.
    struct Edge {
        int src;
        int dest;
    };

    inline std::istream& operator>>(std::istream& in, Edge& edge) noexcept
    {
        return in >> edge.src >> edge.dest;
    }

    // Walks through topological sorts in lexicographic order.
    class KahnBacktracker {
    public:
        // Creates a backtracker for the specified graph.
        template<typename EdgesIt, typename ChainIt>
        KahnBacktracker(int order, EdgesIt edges_first, EdgesIt edges_last,
                        ChainIt chain_first, ChainIt chain_last) noexcept;

        // Advances to the next topological sequence, if any.
        // Returns the sequence, or an empty vector if there is none.
        const std::vector<int>& next() noexcept;

    private:
        static constexpr auto no_tip = -1;

        // Attempt to shorten the chain just enough to replace its tip with a
        // lexicographically higher vertex. If this succeeds, returns the
        // vertex that can be inserted at the tip. Otherwise, returns no_tip.
        int retreat() noexcept;

        // Lengthens the chain to produce a completed topological sort.
        void advance() noexcept;

        // Pops a vertex from the chain for subsequent insertion as a root.
        // Increments its forward neighbors' indegrees, then returns it.
        int pop_root_from_chain() noexcept;

        // Pushes a presumably just-extracted root to the chain. Decrements its
        // forward neighbors' indegrees.
        void push_root_to_chain(int src) noexcept;

        // Finds and removes the specified destination vertex as a root.
        // Keeps the roots sorted in ascending order.
        void erase_root(int dest) noexcept;

        // Adds the specified destination vertex as a root.
        // Keeps the roots as a binary minheap (not necessarily fully sorted).
        void insert_root(int dest) noexcept;

        static std::size_t as_size(int count) noexcept;

        std::vector<std::vector<int>> adj_;
        std::vector<int> indegs_;
        std::vector<int> roots_;
        std::vector<int> chain_;
    };

    template<typename EdgesIt, typename ChainIt>
    KahnBacktracker::KahnBacktracker(const int order,
            const EdgesIt edges_first, const EdgesIt edges_last,
            const ChainIt chain_first, const ChainIt chain_last) noexcept
        : adj_(as_size(order) + 1u), indegs_(as_size(order) + 1u), roots_{},
          chain_(chain_first, chain_last)
    {
        const auto exists = [order](const int vertex) noexcept {
            return 0 < vertex && vertex <= order;
        };

        std::for_each(edges_first, edges_last, [&](const Edge edge) noexcept {
            ensure(exists(edge.src) && exists(edge.dest));
            adj_[edge.src].push_back(edge.dest);
        });

        roots_.reserve(order);

        ensure(std::all_of(cbegin(chain_), cend(chain_), exists));
        ensure(chain_.size() == as_size(order));
    }

    const std::vector<int>& KahnBacktracker::next() noexcept
    {
        // Shorten the chain only as much as necessary.
        const auto src = retreat();

        if (src == no_tip) {
            assert(chain_.empty());
        } else {
            // Push the next bigger vertex at the tip of the chain.
            push_root_to_chain(src);

            // Build the rest of the chain, smallest vertices first.
            advance();
        }

        return chain_;
    }

    int KahnBacktracker::retreat() noexcept
    {
        while (!chain_.empty()) {
            const auto src = pop_root_from_chain();
            const auto first = begin(roots_), last = end(roots_);
            const auto src_pos = std::upper_bound(first, last, src);

            if (src_pos != last) {
                // Get the new src from roots and return the old src.
                return std::exchange(*src_pos, src);
            }

            roots_.push_back(src);
        }

        return no_tip;
    }

    void KahnBacktracker::advance() noexcept
    {
        while (!roots_.empty()) {
            std::pop_heap(begin(roots_), end(roots_), std::greater<>{});
            const auto src = roots_.back();
            roots_.pop_back();

            push_root_to_chain(src);
        }
    }

    int KahnBacktracker::pop_root_from_chain() noexcept
    {
        const auto src = chain_.back();
        chain_.pop_back();

        for (const auto dest : adj_[src])
            if (indegs_[dest]++ == 0) erase_root(dest);

        return src;
    }

    void KahnBacktracker::push_root_to_chain(const int src) noexcept
    {
        for (const auto dest : adj_[src])
            if (--indegs_[dest] == 0) insert_root(dest);

        chain_.push_back(src);
    }

    void KahnBacktracker::erase_root(const int dest) noexcept
    {
        const auto first = begin(roots_), last = end(roots_);
        const auto dest_pos = std::lower_bound(first, last, dest);
        assert(dest_pos != last); // The root must be present.
        roots_.erase(dest_pos);
    }

    void KahnBacktracker::insert_root(const int dest) noexcept
    {
        roots_.push_back(dest);
        std::push_heap(begin(roots_), end(roots_), std::greater<>{});
    }

    inline std::size_t KahnBacktracker::as_size(const int count) noexcept
    {
        // A graph can't have negatively many vertices, and this implementation
        // doesn't accommodate empty graphs.
        ensure(count > 0);
        return static_cast<std::size_t>(count);
    }

    // Given the number of edges in the graph, reads the edges.
    std::vector<Edge> read_edges(const int edge_count) noexcept
    {
        ensure(edge_count >= 0);
        std::vector<Edge> edges (edge_count);

        // I'm not using an istream_iterator here, because (a) its constructor
        // consumes input and I want this to work even when the edge count is
        // zero, and (b) http://cplusplus.github.io/LWG/lwg-active.html#2471.
        for (auto& edge : edges) std::cin >> edge;
        return edges;
    }

    // Given the order (vertex count) of the graph, reads the initial toposort.
    std::vector<int> read_chain(const int order) noexcept
    {
        ensure(order >= 0);
        std::vector<int> chain (order);

        // I'm avoiding istream_iterator here too. See comment in read_edges().
        for (auto& vertex : chain) std::cin >> vertex;
        return chain;
    }

    // Prints a toposort.
    void print_chain(const std::vector<int>& chain) noexcept
    {
        auto sep = "";
        for (const auto vertex : chain) {
            std::cout << sep << vertex;
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    int order {}, edge_count {};

    std::cin >> order >> edge_count;
    const auto edges = read_edges(edge_count);
    const auto chain = read_chain(order);
    ensure(std::cin);

    KahnBacktracker bt {order, cbegin(edges), cend(edges),
                               cbegin(chain), cend(chain)};
    const auto& result = bt.next();

    if (result.empty()) {
        std::cout << "-1\n";
    } else {
        print_chain(result);
    }
}
