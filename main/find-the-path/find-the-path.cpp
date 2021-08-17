#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

namespace {
    template<typename T>
    class ReusableMinHeap
            : public std::priority_queue<T, std::vector<T>, std::greater<>> {
    public:
        void clear() noexcept { this->c.clear(); }
    };

    using Grid = std::vector<std::vector<int>>;

    Grid read_grid() noexcept
    {
        Grid::size_type nrows {}, ncols{};
        std::cin >> nrows >> ncols;

        Grid grid (nrows, std::vector<int>(ncols));
        for (auto& grid_row : grid)
            for (auto& grid_cell : grid_row) std::cin >> grid_cell;

        return grid;
    }

    inline std::size_t height(const Grid& grid) noexcept
    {
        return grid.size();
    }

    inline std::size_t width(const Grid& grid) noexcept
    {
        return grid.front().size();
    }

    struct Pos {
        std::size_t row;
        std::size_t col;
    };

    constexpr bool operator==(const Pos& lhs, const Pos& rhs) noexcept
    {
        return lhs.row == rhs.row && lhs.col == rhs.col;
    }

    constexpr bool operator!=(const Pos& lhs, const Pos& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    constexpr bool operator<(const Pos& lhs, const Pos& rhs) noexcept
    {
        return lhs.row < rhs.row || (lhs.row == rhs.row && lhs.col < rhs.col);
    }

    [[gnu::unused]]
    constexpr bool operator>(const Pos& lhs, const Pos& rhs) noexcept
    {
        return !(lhs < rhs) && lhs != rhs;
    }

    [[gnu::unused]]
    constexpr bool operator<=(const Pos& lhs, const Pos& rhs) noexcept
    {
        return !(rhs < lhs);
    }

    [[gnu::unused]]
    constexpr bool operator>=(const Pos& lhs, const Pos& rhs) noexcept
    {
        return !(lhs < rhs);
    }

    inline std::istream& operator>>(std::istream& in, Pos& pos)
    {
        return in >> pos.row >> pos.col;
    }

    using Query = std::pair<Pos, Pos>;

    std::vector<Query> read_queries() noexcept
    {
        std::vector<Query>::size_type nqueries {};
        std::cin >> nqueries;

        std::vector<Query> queries (nqueries);
        for (auto& query : queries) std::cin >> query.first >> query.second;
        return queries;
    }

    using QueryIndex = std::size_t;

    std::vector<QueryIndex>
    make_query_indices(const std::vector<Query>& queries) noexcept
    {
        std::vector<QueryIndex> indices (queries.size());
        const auto first = begin(indices), last = end(indices);
        std::iota(first, last, QueryIndex{});

        std::sort(first, last, [&](const auto lhs, const auto rhs) noexcept {
            return queries[lhs].first < queries[rhs].first;
        });

        return indices;
    }

    struct Cell {
        constexpr Cell(const Pos pos_, const int cost_) noexcept
            : pos{pos_}, cost{cost_} { }

        Pos pos;
        int cost;
    };

    [[gnu::unused]]
    constexpr bool operator<(const Cell& lhs, const Cell& rhs) noexcept
    {
        return lhs.cost < rhs.cost;
    }

    constexpr bool operator>(const Cell& lhs, const Cell& rhs) noexcept
    {
        return lhs.cost > rhs.cost;
    }

    class ShortestPaths {
    public:
        explicit ShortestPaths(Grid grid) noexcept;

        // Finds the minimum cost from src to dest, by running Dijkstra's
        // algorithm from src. If the last call had the same value of src, then
        // the cached result of Dijkstra's algorithm is used. (For efficiency,
        // group calls with the same value of src together.)
        int operator()(Pos src, Pos dest) noexcept;

    private:
        // Computes the minimum costs of paths from src_ to all destinations.
        void compute() noexcept;

        // Sets all costs to infinity.
        void reset_costs() noexcept;

        // Obtains the cost delta from landing on the specified position.
        int weight(const Pos pos) const noexcept;

        // Obtains the cost to get to pos (from the last-computed source).
        int cost(Pos pos) const noexcept;

        // Obtains and allows modification of the cost to get to pos.
        int& cost(Pos pos) noexcept;

        // Adds the pair (neighbor, cost) to the minheaep.
        void push(Pos neighbor, int cost) noexcept;

        static constexpr Pos no_pos {std::numeric_limits<std::size_t>::max(),
                                     std::numeric_limits<std::size_t>::max()};

        static constexpr auto infinity = std::numeric_limits<int>::max();

        ReusableMinHeap<Cell> heap_;
        std::vector<std::vector<int>> costs_;
        const Grid grid_;
        Pos src_ {no_pos};
        const std::size_t nrows_;
        const std::size_t ncols_;
    };

    ShortestPaths::ShortestPaths(Grid grid) noexcept
        : costs_(height(grid), std::vector<int>(width(grid))), // just zeros
          grid_(std::move(grid)), nrows_{height(grid_)}, ncols_{width(grid_)}
    {
    }

    int ShortestPaths::operator()(const Pos src, const Pos dest) noexcept
    {
        if (src_ != src) {
            src_ = src;
            compute();
        }

        return cost(dest);
    }

    void ShortestPaths::compute() noexcept
    {
        reset_costs();
        heap_.emplace(src_, weight(src_));

        for (auto dests_remaining = nrows_ * ncols_; ; ) {
            const auto cell = heap_.top();
            heap_.pop();
            auto& stored_cost = cost(cell.pos);
            if (stored_cost != infinity) continue;

            stored_cost = cell.cost;
            if (--dests_remaining == 0u) break;

            if (cell.pos.row != 0u)
                push({cell.pos.row - 1u, cell.pos.col}, cell.cost);
            if (cell.pos.row + 1u != nrows_)
                push({cell.pos.row + 1u, cell.pos.col}, cell.cost);
            if (cell.pos.col != 0u)
                push({cell.pos.row, cell.pos.col - 1u}, cell.cost);
            if (cell.pos.col + 1u != ncols_)
                push({cell.pos.row, cell.pos.col + 1u}, cell.cost);
        }

        heap_.clear();
    }

    void ShortestPaths::reset_costs() noexcept
    {
        for (auto& cost_row : costs_)
            std::fill(begin(cost_row), end(cost_row), infinity);
    }

    inline int ShortestPaths::weight(const Pos pos) const noexcept
    {
        return grid_[pos.row][pos.col];
    }

    [[gnu::unused]]
    inline int ShortestPaths::cost(const Pos pos) const noexcept
    {
        return costs_[pos.row][pos.col];
    }

    inline int& ShortestPaths::cost(const Pos pos) noexcept
    {
        return costs_[pos.row][pos.col];
    }

    inline void ShortestPaths::push(const Pos neighbor, const int cost) noexcept
    {
        heap_.emplace(neighbor, cost + weight(neighbor));
    }

    constexpr Pos ShortestPaths::no_pos;

    constexpr int ShortestPaths::infinity;
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    ShortestPaths solver {read_grid()};
    const auto queries = read_queries();

    std::vector<int> replies (queries.size());
    for (const auto index : make_query_indices(queries))
        replies[index] = solver(queries[index].first, queries[index].second);

    for (const auto reply : replies) std::cout << reply << '\n';
}
