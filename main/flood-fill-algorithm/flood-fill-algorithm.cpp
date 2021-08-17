#include <functional>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
    using Screen = std::vector<std::vector<int>>;
    using Index = Screen::size_type;

    Screen read_screen(const Index n, const Index m)
    {
        Screen screen (n);

        for (auto& row : screen) {
            row.resize(m);
            for (auto& pixel : row) std::cin >> pixel;
        }

        return screen;
    }

    void write_screen(const Screen& screen)
    {
        auto sep = "";
        for (const auto& row : screen) {
            for (const auto pixel : row) {
                std::cout << sep << pixel;
                sep = " ";
            }
        }

        std::cout << '\n';
    }

    void fill_region(Screen& screen, const Index n, const Index m,
                     const Index x, const Index y, const int k)
    {
        const auto c = screen.at(x).at(y); // current color
        if (c == k) return;

        const std::function<void(Index, Index)> dfs {
                [=, &screen, &dfs](const Index i, const Index j) {
                    if (i < n && j < m && screen[i][j] == c) {
                        screen[i][j] = k;

                        dfs(i, j - 1u);
                        dfs(i, j + 1u);
                        dfs(i - 1u, j);
                        dfs(i + 1u, j);
                    }
                }
        };

        dfs(x, y);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        Index n {}, m {};
        std::cin >> n >> m;
        auto screen = read_screen(n, m);

        Index x {}, y {};
        auto k = 0;
        std::cin >> x >> y >> k;

        fill_region(screen, n, m, x, y, k);
        write_screen(screen);
    }
}
