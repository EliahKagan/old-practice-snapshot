#include <array>
#include <cstddef>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <tuple>

namespace {
    using std::size_t;

    class Board {
    public:
        static constexpr size_t nmax {25}, mmax {25};

        Board(size_t n, size_t m, size_t a = 1u, size_t b = 2u);

        int knightl_bfs(size_t i, size_t j, size_t fi, size_t fj);

    private:
        std::array<std::array<bool, mmax>, nmax> elems_ {};
        const std::size_t n_, m_, a_, b_;

        bool at(const size_t i, const size_t j) const
        {
            // positions outside the board are considered true / visited
            return i >= n_ || j >= m_ || elems_[i][j];
        }

        inline void enqueue_reach(std::queue<std::tuple<size_t, size_t>>& q,
                                  size_t i, size_t j) const;
    };

    Board::Board(const size_t n, const size_t m,
                 const size_t a, const size_t b)
        : n_{n}, m_{m}, a_{a}, b_{b}
    {
        if (n > nmax || m > mmax) throw std::out_of_range{"board too big"};
    }

    int Board::knightl_bfs(size_t i, size_t j, size_t fi, size_t fj)
    {
        std::queue<std::tuple<size_t, size_t>> q;
        q.emplace(i, j);

        for (auto moves = 0; !q.empty(); ++moves) {
            for (auto len = q.size(); len != 0u; --len) {
                std::tie(i, j) = q.front();
                q.pop();
                if (at(i, j)) continue;
                
                elems_[i][j] = true;
                if (i == fi && j == fj) return moves;

                enqueue_reach(q, i, j);
            }
        }

        return -1;
    }

    inline void Board::enqueue_reach(std::queue<std::tuple<size_t, size_t>>& q,
                                     const size_t i, const size_t j) const
    {
        q.emplace(i + a_, j + b_);
        q.emplace(i + a_, j - b_);
        q.emplace(i + b_, j + a_);
        q.emplace(i + b_, j - a_);
        q.emplace(i - a_, j + b_);
        q.emplace(i - a_, j - b_);
        q.emplace(i - b_, j + a_);
        q.emplace(i - b_, j - a_);
    }
}

namespace {
    static_assert(Board::nmax == Board::mmax, "max board is not square");

    constexpr auto max_reach = Board::nmax - 1u;

    using Table = std::array<std::array<int, max_reach>, max_reach>;

    size_t read_reach()
    {
        size_t n {};
        std::cin >> n;

        const auto reach = n - 1u;
        if (reach > max_reach) throw std::out_of_range{"table too big"};

        return reach;
    }

    void compute_off_diagonal(Table& tab, const size_t reach)
    {
        for (size_t r {0u}; r != reach; ++r) {
            for (auto c = r + 1u; c != reach; ++c) {
                Board b {reach + 1u, reach + 1u, r + 1u, c + 1u};
                tab[r][c] = tab[c][r] = b.knightl_bfs(0u, 0u, reach, reach);
            }
        }
    }

    void compute_on_diagonal(Table& tab, const size_t reach)
    {
        for (size_t d {0u}; d != reach; ++d) { // can optimize diagonal (a==b)
            const auto e = d + 1u;
            tab[d][d] = (reach % e == 0u ? static_cast<int>(reach / e) : -1);
        }
    }

    void print(const Table& tab, const size_t reach)
    {
        for (size_t i {0u}; i != reach; ++i) {
            auto sep = "";

            for (size_t j {0u}; j != reach; ++j) {
                std::cout << sep << tab[i][j];
                sep = " ";
            }

            std::cout << '\n';
        }
    }
}

int main()
{
    const auto reach = read_reach();
    Table tab {};

    compute_off_diagonal(tab, reach);
    compute_on_diagonal(tab, reach);

    print(tab, reach);
}
