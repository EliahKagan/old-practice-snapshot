#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    inline void ensure(const bool condition) noexcept
    {
        if (!condition) std::abort();
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
        std::vector<int> next() noexcept;

    private:
        // Attempt to shorten the chain just enough to replace its tip with a
        // lexicographically higher vertex. If this succeeds, performs that
        // replacement. Otherwise, leaves the chain empty.
        void retreat() noexcept;

        // Lengthens the chain to produce a completed topological sort.
        void advance() noexcept;

        // Finds and removes the specified destination vertex as a root.
        void erase_root(int dest) noexcept;

        static std::size_t as_size(int count) noexcept;

        std::vector<std::vector<int>> adj_;
        std::vector<int> indegs_;
        std::vector<int> roots_;
        std::vector<int> chain_;
    };

    template<typename EdgesIt, typename ChainIt>
    KahnBacktracker::KahnBacktracker(const int order,
            const EdgesIt edges_first, const EdgesIt edges_last,
            const ChainIt chain_first, const ChainIt chain_last)
        : adj_(as_size(order) + 1u), indegs_(as_size(order) + 1u), roots_{},
          chain_(chain_first, chain_last)
    {
        const auto exists = [order](const int vertex) noexcept {
            return 0 < vertex && vertex <= order;
        };

        std::for_each(edges_first, edges_last, [&](const Edge edge) noexcept {
            ensure(exists(edge.src, edge.dest));
            adj_[src].push_back(dest);
        });

        roots_.reserve(order);

        ensure(std::all_of(cbegin(chain_), cend(chain_), exists));
        ensure(chain_.size() == order);
    }

    std::vector<int> KahnBacktracker::next() noexcept
    {
        // FIXME: implement this
    }

    void KahnBacktracker::retreat() noexcept
    {
        while (!chain_.empty()) {
            const auto src = chain_.back();
            chain_.pop_back();

            for (const auto dest : adj_[src])
                if (indegs_[dest]++ == 0) erase_root(dest);

            const auto first = begin(roots_), last = end(roots_);
            const auto src_pos = std::upper_bound(first, last, src);

            if (src_pos != last) {
                // Get the new src from roots and put the old src in its place.
                chain_.push_back(*src_pos);
                *src_pos = src;
                break;
            }

            roots_.push_back(src);
        }
    }

    void KahnBaktracker::advance() noexcept
    {
        for (const auto dest : adj_[src]) {

        }
    }

    void KahnBacktracker::erase_root(const int dest) noexcept
    {
        const auto first = begin(roots_), last = end(roots_);
        const auto dest_pos = std::lower_bound(first, last, dest);
        assert(dest_pos != last); // The root must be present.
        roots_.erase(dest_pos);
    }

    inline std::size_t KahnBacktracker::as_size(const int count) noexcept
    {
        // A graph can't have negatively many vertices, and this implementation
        // doesn't accommodate empty graphs.
        ensure(count > 0);
        return static_cast<std::size_t>(count);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

}
