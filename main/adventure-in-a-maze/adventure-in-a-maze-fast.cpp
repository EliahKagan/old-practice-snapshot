#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

namespace {
    template<typename T>
    using Grid = std::vector<std::vector<T>>;

    template<typename T>
    Grid<T> make_blank_grid(const std::size_t size)
    {
        Grid<T> grid (size);
        for (auto& row : grid) row.resize(size);
        return grid;
    }

    Grid<int> read_maze()
    {
        std::size_t n;
        (void)std::scanf("%zu", &n);
        Grid<int> maze (n);

        for (auto& row : maze) {
            row.resize(n);
            for (auto& elem : row) (void)std::scanf("%d", &elem);
        }

        return maze;
    }

    constexpr auto mod = 1000000007;
    constexpr auto right_only = 1, down_only = 2, right_or_down = 3;

    class Game {
    public:
        explicit Game(const Grid<int>& maze);

        int get_modular_path_count() const { return paths_.back().back(); }
        int get_maximum_adventure() const { return adventure_.back().back(); }

    private:
        void populate_top_left_corner();
        void populate_top_row();
        void populate_left_column();
        void populate_everything_else();

        const std::size_t size_;
        const Grid<int>& maze_;
        Grid<int> paths_;     // can wrap to 0, so don't use for reachability
        Grid<int> adventure_; // but this *can* be used for reachability (!= 0)
    };

    Game::Game(const Grid<int>& maze)
        : size_{maze.size()},
          maze_{maze},
          paths_(make_blank_grid<int>(size_)),
          adventure_(make_blank_grid<int>(size_))
    {
        if (size_ == 0u) std::abort();

        populate_top_left_corner();
        populate_top_row();
        populate_left_column();
        populate_everything_else();
    }

    void Game::populate_top_left_corner()
    {
        adventure_[0u][0u] = maze_[0u][0u];
        paths_[0u][0u] = 1;
    }

    void Game::populate_top_row()
    {
        for (std::size_t j {1u}; j != size_; ++j) {
            if (maze_[0u][j - 1u] == down_only) break;
            adventure_[0u][j] = maze_[0u][j] + adventure_[0u][j - 1u];
            paths_[0u][j] = 1;
        }
    }

    void Game::populate_left_column()
    {
        for (std::size_t i {1u}; i != size_; ++i) {
            if (maze_[i - 1u][0u] == right_only) break;
            adventure_[i][0u] = maze_[i][0u] + adventure_[i - 1u][0u];
            paths_[i][0u] = 1;
        }
    }

    void Game::populate_everything_else()
    {
        for (std::size_t i {1u}; i != size_; ++i) {
            for (std::size_t j {1u}; j != size_; ++j) {
                const auto fell = adventure_[i - 1u][j] != 0
                                    && maze_[i - 1u][j] != right_only;
                const auto slid = adventure_[i][j - 1u] != 0
                                    && maze_[i][j - 1u] != down_only;

                if (!(fell || slid)) continue;

                if (fell) {
                    adventure_[i][j] = std::max(adventure_[i][j],
                                                adventure_[i - 1u][j]);
                    paths_[i][j] += paths_[i - 1u][j];
                }

                if (slid) {
                    adventure_[i][j] = std::max(adventure_[i][j],
                                                adventure_[i][j - 1u]);
                    paths_[i][j] += paths_[i][j - 1u];
                }

                adventure_[i][j] += maze_[i][j];
                paths_[i][j] %= mod;
            }
        }
    }
}

int main()
{
    auto t = 0;
    for ((void)std::scanf("%d", &t); t > 0; --t) {
        const auto maze = read_maze();
        const Game game {maze};
        std::printf("%d %d\n", game.get_modular_path_count(),
                               game.get_maximum_adventure());
    }
}
