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

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        size_t n {}, m {}, i {}, j {}, fi {}, fj {};
        std::cin >> n >> m >> i >> j >> fi >> fj;

        // indices read from from standard input are 1-based (so decrement)
        std::cout << Board{n, m}.knightl_bfs(--i, --j, --fi, --fj) << '\n';
    }
}
