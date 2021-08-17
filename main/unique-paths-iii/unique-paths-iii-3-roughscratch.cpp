class Solution {
public:
    static int uniquePathsIII(const vector<vector<int>>& rows) noexcept;
};

namespace {
    class BitMatrix {
    private:
        static constexpr auto max_area = 20;

        using BitSet = bitset<max_area>;

    public:
        using reference = BitSet::reference;

        constexpr BitMatrix(const int height, const int width) noexcept
            : height_{height}, width_{width} { assert(area() <= max_area); }

        constexpr int height() const noexcept { return height_; }

        constexpr int width() const noexcept { return width_; }

        constexpr int area() const noexcept { return height_ * width_; }

        [[maybe_unused]]
        constexpr bool operator()(const int i, const int j) const noexcept
            { return bits_[index(i, j)]; }

        reference operator()(const int i, const int j) noexcept
            { return bits_[index(i, j)]; }

    private:
        constexpr int index(const int i, const int j) const noexcept
        {
            //assert(0 <= i && i < height_);
            //assert(0 <= j && j < width_);
            return i * height_ + j; // FIXME: Should be: i * width_ + j
        }

        BitSet bits_ {};
        const int height_, width_;
    };

    class Board {
    public:
        // Initializes and populates the board.
        explicit Board(const vector<vector<int>>& rows) noexcept;

        // Counts start-to-finish paths that hit every non-blocked cell once.
        int count_paths() noexcept;

    private:
        // Retrieves the height of the grid.
        static int get_height(const vector<vector<int>>& rows) noexcept;

        // Retrieves the width (of the first row) of the grid.
        // Assumes height > 0.
        static int get_width(const vector<vector<int>>& rows) noexcept;

        // Counts paths on a possibly-mutated board from (i, j) to finish
        // that hit every non-blocked cell once. [Helper for count_paths().]
        int dfs(int remaining, int i, int j) noexcept;

        BitMatrix cells_;
        int start_remaining_;
        int start_i_ {}, start_j_ {}, finish_i_ {}, finish_j_ {};
    };

    Board::Board(const vector<vector<int>>& rows) noexcept
        : cells_{get_height(rows), get_width(rows)},
          start_remaining_{cells_.area() - 1}
    {
        for (auto i = 0; i != cells_.height(); ++i) {
            for (auto j = 0; j != cells_.width(); ++j) {
                switch (rows[i][j]) {
                case 0:
                    break;
                case -1:
                    cells_(i, j) = true;
                    --start_remaining_;
                    break;
                case 1:
                    start_i_ = i;
                    start_j_ = j;
                    break;
                case 2:
                    finish_i_ = i;
                    finish_j_ = j;
                    break;
                default:
                    abort();
                }
            }
        }
    }

    int Board::count_paths() noexcept
    {
        return dfs(start_remaining_, start_i_, start_j_);
    }

    inline int Board::get_height(const vector<vector<int>>& rows) noexcept
    {
        using std::size;
        return static_cast<int>(size(rows));
    }

    inline int Board::get_width(const vector<vector<int>>& rows) noexcept
    {
        using std::size;
        return static_cast<int>(size(rows.front()));
    }

    int Board::dfs(const int remaining, const int i, const int j) noexcept
    {
        if (i == -1 || i == cells_.height() || j == -1 || j == cells_.width()
                || cells_(i, j))
            return 0;

        const auto filled = remaining == 0;
        const auto at_end = i == finish_i_ && j == finish_j_;
        if (filled || at_end) return +(filled && at_end);

        cells_(i, j) = true;

        const auto sum = dfs(remaining - 1, i, j - 1)
                       + dfs(remaining - 1, i, j + 1)
                       + dfs(remaining - 1, i - 1, j)
                       + dfs(remaining - 1, i + 1, j);

        cells_(i, j) = false;

        return sum;
    }
}

int Solution::uniquePathsIII(const vector<vector<int>>& rows) noexcept
{
    return Board{rows}.count_paths();
}
