#include <array>
#include <cstddef>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>

namespace {
    using std::size_t;

    constexpr size_t nmax = 100;
    using Board = std::array<std::array<bool, nmax>, nmax>;

    Board read_board(const size_t n) // true cells are accessible
    {
        if (n == 0u || n > nmax) throw std::out_of_range("board too big");

        Board board {};

        for (size_t i {0u}; i != n; ++i) {
            std::string row;
            std::cin >> row;
            for (size_t j = 0; j != n; ++j) board[i][j] = row[j] == '.';
        }

        return board;
    }

    int count_moves(const size_t n, const Board& board,
                    size_t a, size_t b, const size_t c, const size_t d)
    {
        auto untouched = board;
        std::queue<std::tuple<size_t, size_t>> q;

        const auto enqueue_if_reachable = [n, &board, &untouched, &q]
                                          (const size_t i, const size_t j) {
            if (i < n && j < n && board[i][j]) {
                if (untouched[i][j]) {
                    untouched[i][j] = false;
                    q.emplace(i, j);
                }

                return true;
            }

            return false;
        };

        const auto dequeue = [&a, &b, c, d, &q]() {
            std::tie(a, b) = q.front();
            q.pop();
            return a == c && b == d;
        };

        enqueue_if_reachable(a, b);

        for (auto moves = 0; !q.empty(); ++moves) {
            for (auto len = q.size(); len != 0; --len) {
                if (dequeue()) return moves;

                for (size_t j {b}; enqueue_if_reachable(a, ++j); ) { }
                for (size_t j {b}; enqueue_if_reachable(a, --j); ) { }
                for (size_t i {a}; enqueue_if_reachable(++i, b); ) { }
                for (size_t i {a}; enqueue_if_reachable(--i, b); ) { }
            }
        }

        return -1; // destination unreachable
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    size_t n {};
    std::cin >> n;

    const auto board = read_board(n);

    size_t a {}, b {}, c {}, d {};
    std::cin >> a >> b >> c >> d;

    std::cout << count_moves(n, board, a, b, c, d) << '\n';
}
