#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <stdexcept>

namespace {
    constexpr std::size_t visited {0u}, ending {100u}, max_roll {6u};

    using Board = std::array<std::size_t, ending + 1u>;

    inline void validate(const std::size_t pos)
    {
        if (pos == 0u || pos > ending)
            throw std::out_of_range{"position outside board"};
    }

    void read_connections(Board& board)
    {
        int n = 0;
        for (std::cin >> n; n > 0; --n) {
            std::size_t src {}, dest {};
            std::cin >> src >> dest;
            
            validate(src);
            validate(dest);

            board[src] = dest;
        }
    }

    Board read_board()
    {
        Board board;
        std::iota(std::begin(board), std::end(board), 0u);

        read_connections(board); // ladders
        read_connections(board); // snakes

        return board;
    }

    inline void enqueue_reach(std::queue<std::size_t>& q,
                              const std::size_t src)
    {
        for (auto dest = std::min(ending, src + max_roll); dest != src; --dest)
            q.push(dest);
    }

    int bfs(Board& board)
    {
        std::queue<std::size_t> q;
        q.push(1u);

        for (auto turns = 0; !q.empty(); ++turns) {
            for (auto len = q.size(); len != 0u; --len) {
                const auto pos = board[q.front()];
                q.pop();
                
                switch (board[pos]) {
                case visited:
                    continue;

                case ending:
                    return turns;

                default:
                    board[pos] = visited;
                    enqueue_reach(q, pos);
                }
            }
        }

        return -1;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto board = read_board();
        std::cout << bfs(board) << '\n';
    }
}
