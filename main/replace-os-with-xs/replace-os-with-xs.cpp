#include <cassert>
#include <iostream>
#include <vector>

namespace {
    using Row = std::vector<char>;
    using Grid = std::vector<Row>;

    Grid read_grid(const Grid::size_type n, const Row::size_type m)
    {
        Grid a (n);
        for (auto& row : a) {
            row.resize(m);
            for (auto& c : row) std::cin >> c;
        }

        return a;
    }

    void print_grid(const Grid& a)
    {
        auto sep = "";

        for (const auto& row : a) {
            for (const auto& c : row) {
                std::cout << sep << c;
                sep = " ";
            }
        }

        std::cout << '\n';
    }

    void mark(Grid& a, const Grid::size_type n, const Row::size_type m,
                       const Grid::size_type i, const Row::size_type j)
    {
        if (i < n && j < m && a[i][j] == 'O') { // unsigned i, j wrap around
            a[i][j] = 'o';

            mark(a, n, m, i - 1u, j);
            mark(a, n, m, i + 1u, j);
            mark(a, n, m, i, j - 1u);
            mark(a, n, m, i, j + 1u);
        }
    }

    void mark_exterior_regions(Grid& a, const Grid::size_type n,
                                        const Row::size_type m)
    {
        // mark everything reachable from anything in the top and bottom rows
        for (Row::size_type j {0u}; j != m; ++j) {
            mark(a, n, m, 0u, j);
            mark(a, n, m, n - 1u, j);
        }

        // mark everything reachable from the side columns (corner overlap OK)
        for (Grid::size_type i {0u}; i != n; ++i) {
            mark(a, n, m, i, 0u);
            mark(a, n, m, i, m - 1u);
        }
    }

    void erase_interior_regions(Grid& a, const Grid::size_type n,
                                         const Row::size_type m)
    {
        mark_exterior_regions(a, n, m);

        for (auto& row : a) {
            for (auto& c : row) {
                switch (c) {
                case 'O':
                    c = 'X'; // erase unmarked 'O's (i.e., make them 'X's)
                    break;

                case 'o':
                    c = 'O'; // an 'o' is a protected 'O'; restore it
                    break;

                default:
                    assert(c == 'X');
                }
            }
        }
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        Grid::size_type n {};
        Row::size_type m {};
        std::cin >> n >> m;
        
        auto a = read_grid(n, m);
        erase_interior_regions(a, n, m);
        print_grid(a);
    }
}
