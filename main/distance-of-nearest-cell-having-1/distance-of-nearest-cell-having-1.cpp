#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
    constexpr std::size_t nmax{20u}, mmax{20u};

    class DistanceMatrix {
    public:
        explicit DistanceMatrix(std::istream& in);

        std::size_t n() const { return n_; }
        std::size_t m() const { return m_; }

        inline int at(std::size_t i, std::size_t j) const;

    private:
        static std::size_t get(std::istream& in, int max);

        std::array<std::array<int, nmax>, mmax> elems_{};
        const std::size_t n_, m_;

        void populate(std::istream& in);
        void dfs_fill(std::size_t i, std::size_t j, int d); // taxicab metric
        void compute();
    };

    DistanceMatrix::DistanceMatrix(std::istream& in)
        : n_{get(in, nmax)}, m_{get(in, mmax)}
    {
        populate(in);
        compute();
    }

    inline int DistanceMatrix::at(const std::size_t i,
                                  const std::size_t j) const
    {
        if (i >= n_ || j >= m_) throw std::out_of_range{"index out of range"};
        return elems_[i][j];
    }

    std::size_t DistanceMatrix::get(std::istream& in, const int max)
    {
        auto x = 0;
        in >> x;
        if (x < 0 || x > max) throw std::out_of_range{"invalid matrix size"};
        return static_cast<std::size_t>(x);
    }

    void DistanceMatrix::populate(std::istream& in)
    {
        for (std::size_t i {0u}; i != n_; ++i) {
            for (std::size_t j {0u}; j != m_; ++j) {
                auto e = false;
                in >> e;
                elems_[i][j] = (e ? 0 : std::numeric_limits<int>::max());
            }
        }
    }

    void DistanceMatrix::dfs_fill(const std::size_t i, const std::size_t j,
                                  const int d)
    {
        static constexpr auto npos = static_cast<std::size_t>(-1);

        if (i == n_ || i == npos || j == m_ || j == npos || elems_[i][j] <= d)
            return;

        elems_[i][j] = d;

        dfs_fill(i, j - 1u, d + 1);
        dfs_fill(i, j + 1u, d + 1);
        dfs_fill(i - 1u, j, d + 1);
        dfs_fill(i + 1u, j, d + 1);
    }

    void DistanceMatrix::compute()
    {
        for (std::size_t i{0u}; i != n_; ++i) {
            for (std::size_t j{0u}; j != m_; ++j) {
                if (elems_[i][j] == 0) {
                    elems_[i][j] = 1; // so dfs_fill knows there is work to do
                    dfs_fill(i, j, 0);
                }
            }
        }
    }

    bool pretty = false;

    void print_pretty(std::ostream& out, const DistanceMatrix& grid)
    {
        for (std::size_t i {0u}; i != grid.n(); ++i) {
            auto sep = "";

            for (std::size_t j {0u}; j != grid.m(); ++j) {
                out << sep << grid.at(i, j);
                sep = " ";
            }

            out << '\n';
        }
    }

    void print_ugly(std::ostream& out, const DistanceMatrix& grid)
    {
        auto sep = "";

        for (std::size_t i {0u}; i != grid.n(); ++i) {
            for (std::size_t j {0u}; j != grid.m(); ++j) {
                out << sep << grid.at(i, j);
                sep = " ";
            }
        }

        out << '\n';
    }

    std::ostream& operator<<(std::ostream& out, const DistanceMatrix& grid)
    {
        if (pretty) print_pretty(out, grid);
        else        print_ugly(out, grid);

        return out;
    }

    inline bool starts_with(const std::string& s, const std::string& t)
    {
        return s.substr(0u, t.size()) == t;
    }

    void apply_print_style(const int argc, char** const argv)
    {
        std::for_each(argv + 1, argv + static_cast<std::ptrdiff_t>(argc),
                      [](const std::string arg) { //-V801 would still construct
            if (starts_with(arg, "-") && !starts_with(arg, "--")) {
                std::for_each(++arg.cbegin(), arg.cend(), [](const char c) {
                    switch (c) {
                    case 'p':
                        pretty = true;
                        break;

                    case 'u':
                        pretty = false;
                        break;

                    default:
                        ; // do nothing (don't warn on spurious flags)
                    }
                });
            }
        });
    }
}

int main(int argc, char** argv)
{
    apply_print_style(argc, argv); // allow -p for debugging (and fun)

    auto t = 0;
    for (std::cin >> t; t > 0; --t) std::cout << DistanceMatrix{std::cin};
}
