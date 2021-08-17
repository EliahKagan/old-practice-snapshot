#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <vector>

namespace {
    template<typename T>
    using MinHeap = std::priority_queue<T, std::vector<T>, std::greater<>>;

    using Grid = std::vector<std::vector<int>>;

    Grid read_grid()
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

    inline std::istream& operator>>(std::istream& in, Pos& pos)
    {
        return in >> pos.row >> pos.col;
    }

    struct Cell {
        constexpr Cell(const Pos pos_, const int cost_) noexcept
            : pos{pos_}, cost{cost_} { }

        Pos pos;
        int cost;
    };

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

        // Computes the cost of the minimum-cost path from src to dest.
        int operator()(Pos src, Pos dest);

    private:
        int weight(const Pos pos) const noexcept;

        int cost(Pos pos) const noexcept;

        int& cost(Pos pos) noexcept;

        void reset() noexcept;

        static constexpr auto infinity = std::numeric_limits<int>::max();

        MinHeap<Cell> heap_;
        std::vector<std::vector<int>> costs_;
        const Grid grid_;
        const std::size_t nrows_;
        const std::size_t ncols_;
    };

    ShortestPaths::ShortestPaths(Grid grid) noexcept
        : costs_(height(grid), std::vector<int>(width(grid), infinity)),
          grid_(std::move(grid)), nrows_{height(grid_)}, ncols_{width(grid_)}
    {
    }

    int ShortestPaths::operator()(const Pos src, const Pos dest)
    {
        for (heap_.emplace(src, weight(src)); ; ) {
            const auto cell = heap_.top();
            heap_.pop();
            auto& stored_cost = cost(cell.pos);
            if (stored_cost != infinity) continue;

            stored_cost = cell.cost;
            if (cell.pos == dest) break;

            for (const auto neighbor : {Pos{cell.pos.row - 1u, cell.pos.col},
                                        Pos{cell.pos.row + 1u, cell.pos.col},
                                        Pos{cell.pos.row, cell.pos.col - 1u},
                                        Pos{cell.pos.row, cell.pos.col + 1u}}) {
                if (neighbor.row < nrows_ && neighbor.col < ncols_)
                    heap_.emplace(neighbor, cell.cost + weight(neighbor));
            }
        }

        const auto ret = cost(dest);
        reset();
        return ret;
    }

    inline int ShortestPaths::weight(const Pos pos) const noexcept
    {
        return grid_[pos.row][pos.col];
    }

    inline int ShortestPaths::cost(const Pos pos) const noexcept
    {
        return costs_[pos.row][pos.col];
    }

    inline int& ShortestPaths::cost(const Pos pos) noexcept
    {
        return costs_[pos.row][pos.col];
    }

    void ShortestPaths::reset() noexcept
    {
        // FIXME: clear the heap in such a way as to limit future allocations
        //heap_.clear();
        heap_ = {};

        for (auto& cost_row : costs_)
            std::fill(begin(cost_row), end(cost_row), infinity);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    ShortestPaths solver {read_grid()};

    auto q = 0;
    for (std::cin >> q; q > 0; --q) {
        Pos src {}, dest {};
        std::cin >> src >> dest;
        std::cout << solver(src, dest) << '\n';
    }
}
