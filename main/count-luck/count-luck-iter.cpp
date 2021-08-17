#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <limits>
#include <stack>
#include <string>
#include <tuple>
#include <vector>

namespace {
    using Grid = std::vector<std::string>;

    using Pos = std::tuple<std::size_t, std::size_t>;

    constexpr std::size_t sides {4u};

    constexpr auto trapped = -1;

    Grid read_grid()
    {
        std::size_t height {}, width {};
        std::cin >> height >> width;
        Grid grid (height);

        for (auto& row : grid) {
            std::cin >> row;
            if (row.size() != width) std::abort();
        }

        return grid;
    }

    Pos find_start(const Grid& grid) noexcept
    {
        for (std::size_t i {0u}; i != grid.size(); ++i) {
            for (std::size_t j {0u}; j != grid[i].size(); ++j)
                if (grid[i][j] == 'M') return std::make_tuple(i, j);
        }

        std::abort(); // Crash "nicely" if there is no start location.
    }

    struct Frame {
        Pos pos;
        std::size_t index;
        int junctions;
    };

    constexpr std::array<Pos, sides>
    neighbors(const std::size_t i, const std::size_t j) noexcept
    {
        return {{{i - 1u, j}, {i + 1u, j}, {i, j - 1u}, {i, j + 1u}}};
    }

    inline bool can_go(const Grid& grid,
                       const std::size_t i, const std::size_t j) noexcept
    {
        return i < grid.size() && j < grid[i].size() && grid[i][j] != 'X';
    }

    inline int count_choices(const Grid& grid,
                             const std::size_t i, const std::size_t j) noexcept
    {
        auto choices = 0;

        for (const auto& cell : neighbors(i, j)) {
            std::size_t h {}, k {};
            std::tie(h, k) = cell;
            if (can_go(grid, h, k)) ++choices;
        }

        return choices;
    }

    int count_junctions(Grid& grid, std::size_t i, std::size_t j)
    {
        std::stack<Frame> frames;
        frames.push({{i, j}, 0u, 0});

        while (!frames.empty()) {
            auto& frame = frames.top();

            if (frame.index == sides) {
                frames.pop();
                continue;
            }

            std::tie(i, j) = frame.pos;

            if (frame.index == 0) {
                if (grid[i][j] == '*') return frame.junctions;
                grid[i][j] = 'X';

                const auto choices = count_choices(grid, i, j);

                if (choices == 0) {
                    frames.pop();
                    continue;
                }

                if (choices > 1) ++frame.junctions;
            }

            std::size_t h {}, k {};
            std::tie(h, k) = neighbors(i, j)[frame.index++];
            if (can_go(grid, h, k)) frames.push({{h, k}, 0u, frame.junctions});
        }

        return trapped;
    }
}

int main()
{
    int t {};
    for (std::cin >> t; t > 0; --t) {
        auto grid = read_grid();

        int guess {};
        std::cin >> guess;

        const auto start = find_start(grid);
        std::size_t i {}, j {};
        std::tie(i, j) = start;

        const auto count = count_junctions(grid, i, j);
        std::cout << (count == guess ? "Impressed" : "Oops!") << '\n';
    }
}
