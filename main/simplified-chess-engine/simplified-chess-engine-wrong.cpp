#ifdef NDEBUG
#error Runtime assertions are unexpectedly disabled for this build.
#endif

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <type_traits>

#if __cplusplus >= 201703L
#define FALLTHROUGH fallthrough
#elif defined(__clang__)
#define FALLTHROUGH clang::fallthrough
#elif defined(__GNUC__)
#define FALLTHROUGH gnu::fallthrough
#else
#define FALLTHROUGH
#endif

#define UNREACHABLE(msg) (assert(!static_cast<bool>(msg)))

namespace {
    using std::size_t;

    using EnumBase = unsigned;

    template<typename T>
    constexpr EnumBase base(const T enumerator)
    { 
        static_assert(std::is_enum<T>::value, "not an enumeration type");

        using Unqualified = typename std::remove_cv<T>::type;
        using Underlying = typename std::underlying_type<Unqualified>::type;
        static_assert(std::is_same<Underlying, EnumBase>::value,
                      "not based on EnumBase");

        return static_cast<EnumBase>(enumerator);
    }
    
    enum class Player : EnumBase {
        white =  0u,
        black = 16u
    };

    constexpr Player opponent(const Player player)
    {
        return static_cast<Player>(base(player) ^ base(Player::black));
    }

    static_assert(opponent(Player::white) == Player::black
               && opponent(Player::black) == Player::white,
            "the opponent() function says white and black aren't opponents!");

    enum class Piece : EnumBase {
        queen   = 1u << 0u,
        knight  = 1u << 1u,
        bishop  = 1u << 2u,
        rook    = 1u << 3u,
        pawn    = 1u << 4u
    };

    constexpr auto k_piece_mask = base(Player::black) - 1u;

    // See below for the (Object, Player) => Piece overload.
    constexpr Piece as_piece(const char symbol)
    {
        switch (symbol) {
            case 'Q':   return Piece::queen;
            case 'N':   return Piece::knight;
            case 'B':   return Piece::bishop;
            case 'R':   return Piece::rook;
            case 'P':   return Piece::pawn;

            default:    throw std::out_of_range{"unrecognized piece symbol"};
        }
    }

    enum class Object : EnumBase {
        empty = 0,  // represent the absence of a piece

        white_queen     = base(Piece::queen)    << base(Player::white),
        white_knight    = base(Piece::knight)   << base(Player::white),
        white_bishop    = base(Piece::bishop)   << base(Player::white),
        white_rook      = base(Piece::rook)     << base(Player::white),
        white_pawn      = base(Piece::pawn)     << base(Player::white),

        black_queen     = base(Piece::queen)    << base(Player::black),
        black_knight    = base(Piece::knight)   << base(Player::black),
        black_bishop    = base(Piece::bishop)   << base(Player::black),
        black_rook      = base(Piece::rook)     << base(Player::black),
        black_pawn      = base(Piece::pawn)     << base(Player::black)
    };

    constexpr Object as_object(const Piece piece, const Player player)
    {
        return static_cast<Object>(base(piece) << base(player));
    }

    constexpr bool belongs_to(const Player player, const Object obj)
    {
        return base(obj) & (base(player) << k_piece_mask);
    }

    // See above for the (char) => Piece overload.
    constexpr Piece as_piece(const Object obj, const Player player)
    {
        return static_cast<Piece>(base(obj) >> base(player));
    }

    constexpr size_t k_board_size {4u};

    using Board = std::array<std::array<Object, k_board_size>, k_board_size>;

    constexpr bool on_board(const size_t i, const size_t j)
    {
        // If called with negative values, they get converted to big positive
        // numbers (as size_t is unsigned), so unless they are *huge* negative
        // values, they will be be correctly reported as outside the board.
        return i < k_board_size && j < k_board_size;
    }

    constexpr size_t promotes_at_row(const Player player)
    {
        return player == Player::white ? k_board_size - 1u : 0u;
    }

    constexpr size_t pawn_direction(const Player player)
    {
        // The unsigned representation of -1 is the higest positive value.
        // Since unsigned arithmetic is carried out modulo one greater than
        // that value, adding the unsigned representation of -1 in an unsigned
        // type to a value of that *same* unsigned type causes the value to be
        // decremented, just as though signed arithmetic had been used.
        return static_cast<size_t>(player == Player::white ? +1 : -1);
    }

    void read_pieces(Board& board, const Player player, int count)
    {
        while (count-- > 0) { 
            char symbol {}, file {}, rank {};
            std::cin >> symbol >> file >> rank;
            const auto i = static_cast<size_t>(rank - '1');
            const auto j = static_cast<size_t>(file - 'A');

            if (board.at(i).at(j) != Object::empty)
                throw std::invalid_argument{"board position already occupied"};

            const auto piece = as_piece(symbol);

            if (piece == Piece::pawn && i == promotes_at_row(player))
                throw std::invalid_argument{"pawn at final row would promote"};

            board[i][j] = as_object(piece, player);
        }
    }

    Board read_initial_board(const int white_count, const int black_count)
    {
        if (white_count <= 0 || black_count <= 0)
            throw std::out_of_range{"nonpositive piece count"};

        Board board {};
        read_pieces(board, Player::white, white_count);
        read_pieces(board, Player::black, black_count);
        return board;
    }

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif
    class Game {
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
    public:
        Game(Board& board, int moves,
             Player player = Player::white, bool draw_wins = false);

        bool has_winning_strategy();

    private:
        // These four functions should ideally have only *one* call site each.
        inline bool try_knight_moves(size_t i, size_t j); // knight only
        inline bool try_bishop_moves(size_t i, size_t j); // bishop and queen
        inline bool try_rook_moves(size_t i, size_t j);   // rook and queen
        inline bool try_pawn_moves(size_t i, size_t j);   // pawn only

        // currently only used as a helper function for try_knight_moves()
        inline bool try_one_move_if_open(size_t i, size_t j,
                                         size_t ii, size_t jj);
        
        // helper function for try_bishop_moves() and try_rook_moves()
        inline bool try_moves_in_direction_if_open(size_t i, size_t j,
                                                   size_t di, size_t dj);

        // a way to call that helper function while avoiding compiler warnings
        bool try_moves_in_direction_if_open(const size_t i, const size_t j,
                                            const int di, const int dj)
        {
            return try_moves_in_direction_if_open(
                    i, j, static_cast<size_t>(di), static_cast<size_t>(dj));
        }

        bool try_move(Object& src, Object& dest, Object becomes);

        bool try_move(Object& src, Object& dest)
        {
            return try_move(src, dest, src);
        }

        bool try_move(const size_t i, const size_t j,
                      const size_t ii, const size_t jj,
                      const Object becomes)
        {
            return try_move(board_[i][j], board_[ii][jj], becomes);
        }

        bool try_move(const size_t i, const size_t j,
                      const size_t ii, const size_t jj)
        {
            return try_move(board_[i][j], board_[ii][jj]);
        }

        constexpr Object opponent_queen() const
        {
            return as_object(Piece::queen, opponent(player_));
        }

        Board& board_;
        int moves_;
        Player player_;
        bool draw_wins_;
    };

    Game::Game(Board& board, const int moves,
               const Player player, const bool draw_wins)
        : board_(board), moves_{moves}, player_{player}, draw_wins_{draw_wins}
    {
        if (moves <= 0)
            throw std::out_of_range{"nonpositive number of remaining moves"};
    }

    bool Game::has_winning_strategy()
    {
        for (size_t i {0u}; i != k_board_size; ++i) {
            for (size_t j {0u}; j != k_board_size; ++j) {
                if (!belongs_to(player_, board_[i][j])) continue;

                const auto piece = as_piece(board_[i][j], player_);

                switch (piece) {
                case Piece::knight:
                    if (try_knight_moves(i, j)) return true;
                    continue;

                case Piece::pawn:
                    if (try_pawn_moves(i, j)) return true;
                    continue;

                case Piece::queen:
                case Piece::rook:
                    if (try_rook_moves(i, j)) return true;
                    if (piece == Piece::rook) continue;
                    [[FALLTHROUGH]];

                case Piece::bishop:
                    if (try_bishop_moves(i, j)) return true;
                    continue;
                }

                UNREACHABLE("unrecognized piece on board (shouldn't happen!)");
            }
        }

        return false;
    }

    inline bool Game::try_knight_moves(const size_t i, const size_t j)
    {
        // A knight in chess is mathematically a knight(a, b), where:
        static constexpr size_t a {1u}, b {2u};

        return try_one_move_if_open(i, j, i - a, j - b)
            || try_one_move_if_open(i, j, i - a, j + b)
            || try_one_move_if_open(i, j, i + a, j - b)
            || try_one_move_if_open(i, j, i + a, j + b)
            || try_one_move_if_open(i, j, i - b, j - a)
            || try_one_move_if_open(i, j, i - b, j + a)
            || try_one_move_if_open(i, j, i + b, j - a)
            || try_one_move_if_open(i, j, i + b, j + b);
    }

    inline bool Game::try_bishop_moves(const size_t i, const size_t j)
    {
        return try_moves_in_direction_if_open(i, j, -1, -1)
            || try_moves_in_direction_if_open(i, j, -1, +1)
            || try_moves_in_direction_if_open(i, j, +1, -1)
            || try_moves_in_direction_if_open(i, j, +1, +1);
    }

    inline bool Game::try_rook_moves(const size_t i, const size_t j)
    {
        return try_moves_in_direction_if_open(i, j, 0, -1)
            || try_moves_in_direction_if_open(i, j, 0, +1)
            || try_moves_in_direction_if_open(i, j, -1, 0)
            || try_moves_in_direction_if_open(i, j, +1, 0);
    }

    inline bool Game::try_pawn_moves(const size_t i, const size_t j)
    {
        // FIXME: implement this function!
        UNREACHABLE("pawns are not suppported yet");
        std::abort();
    }

    bool Game::try_one_move_if_open(const size_t i, const size_t j,
                                    const size_t ii, const size_t jj)
    {
        return on_board(ii, jj) && !belongs_to(player_, board_[ii][jj])
                                && try_move(i, j, ii, jj);
    }

    inline bool Game::try_moves_in_direction_if_open(
            const size_t i, const size_t j, const size_t di, const size_t dj)
    {
        // If called with negative values for di or dj, they get converted to
        // big positive numbers. When added to i or j, this wraps around to the
        // same value that would have resulted if actual signed arithmetic were
        // used, so long as that value is positive, because unsigned arithmetic
        // is modular [here, it is modulo std::numeric_limits<size_t>::max()].
        // If that value would be negative, then the positive result will be
        // outside the board as well [see on_board()]. Either way, it works
        // fine to pass values like -1 as di or dj.
        for (auto ii = i, jj = j; on_board(ii += di, jj += dj); ) {
            if (board_[ii][jj] == Object::empty) {
                if (try_move(i, j, ii, jj)) return true;
            } else {
                if (!belongs_to(player_, board_[ii][jj])
                            && try_move(i, j, ii, jj))
                    return true;

                break; // can't move past even a capturable piece
            }
        }

        return false;
    }

    bool Game::try_move(Object& src, Object& dest, Object becomes)
    {
        const auto captured = dest;
        if (captured == opponent_queen()) return true;
        if (moves_ == 0) return draw_wins_;

        dest = becomes;
        becomes = src; // so we can backtrack
        src = Object::empty;
        --moves_;
        player_ = opponent(player_);
        draw_wins_ = !draw_wins_;
        
        // The path up to and including the current move is part of at least
        // one winning strategy for one player if and only if the other player
        // has no winning or draw-forcing strategies from there on. Similarly,
        // it is part of at least one winning or draw-forcing strategy for one
        // player if and only if the other player has no winning strategy from
        // there on. We have entered the next turn and toggled whether a draw
        // "wins" or not, so it is sufficient to determine if the now-"current"
        // player has any strategy to guarantee a "win," and negate the result.
        const auto result = !has_winning_strategy();

        draw_wins_ = !draw_wins_;
        player_ = opponent(player_);
        ++moves_;
        src = becomes; // because we set it up for backtracking
        dest = captured;

        return result;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto g = 0;
    for (std::cin >> g; g > 0; --g) {
        auto white_count = 0, black_count = 0, moves = 0;
        std::cin >> white_count >> black_count >> moves;
        auto board = read_initial_board(white_count, black_count);
        
        std::cout << (Game{board, moves}.has_winning_strategy() ? "YES" : "NO")
                  << '\n';
    }
}
