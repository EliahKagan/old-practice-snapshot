#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {
    // k_white and k_black represent the players, and are used on the right-
    // hand side of << to shift the generic representations of each piece to
    // represent an object consisting of a piece and a color.
    constexpr auto k_white = 0u;
    constexpr auto k_black = 8u;

    constexpr unsigned opponent(const unsigned player)
    {
        return player ^ k_black;
    }

    static_assert(opponent(k_white) == k_black && opponent(k_black) == k_white,
            "the opponent() function says white and black aren't opponents!");

    // Represents the absence of a piece.
    constexpr auto k_empty = 0u;

    // These represent pieces. They are colored (i.e., givan player
    // affiliation) by appearing on the left of << k_white or of << k_black.
    constexpr auto k_queen = 1u;
    constexpr auto k_knight = 2u;
    constexpr auto k_bishop = 3u;
    constexpr auto k_rook = 4u;
    constexpr auto k_pawn = 5u;

    constexpr unsigned piece_from_symbol(const char symbol)
    {
        switch (symbol) {
            case 'Q':   return k_queen;
            case 'N':   return k_knight;
            case 'B':   return k_bishop;
            case 'R':   return k_rook;
            case 'P':   return k_pawn;

            default:    throw std::out_of_range{"unrecognized chessman symbol"};
        }
    }

    constexpr std::size_t k_board_size {4u};

    using Board = std::array<std::array<unsigned, k_board_size>, k_board_size>;

    void read_pieces(Board& board, const unsigned player, int count)
    {
        while (count-- > 0) { 
            char symbol {}, file {}, rank {};
            std::cin >> symbol >> file >> rank;
            const auto i = static_cast<std::size_t>(rank - 'A');
            const auto j = static_cast<std::size_t>(file - '0');

            if (board.at(i).at(j) != k_empty)
                throw std::invalid_argument{"board position already occupied"};

            board[i][j] = piece_from_symbol(symbol) << player;
        }
    }

    Board read_board(const int white_count, const int black_count)
    {
        if (white_count <= 0 || black_count <= 0)
            throw std::out_of_range{"unexpected nonpositive piece count"};

        Board board {};
        read_pieces(board, k_white, white_count);
        read_pieces(board, k_black, black_count);
        return board;
    }

    bool has_winning_strategy(Board& board, const int moves_remaining,
            const unsigned player = k_white, const bool draw_wins = false)
    {

    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto game = 0;
    for (std::cin >> game; game > 0; --game) {
        auto white_count = 0, black_count = 0, moves_remaining = 0;
        std::cin >> white_count >> black_count >> moves_remaining;
        if (moves_remaining <= 0)
            throw std::out_of_range{"unexpected nonpositive moves remaining"};


    }
}
