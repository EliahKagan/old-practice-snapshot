class Solution {
public:
    static int uniquePathsIII(const vector<vector<int>>& rows) noexcept;
};

namespace {
    class Board {
    public:
        // Initializes and populates the board.
        explicit Board(const vector<vector<int>>& rows) noexcept;

        // Counts start-to-finish paths that hit every non-blocked cell once.
        int count_paths() noexcept;

    private:
        static constexpr auto max_dimension = 20;

        // Retrieves the height of the grid.
        static int get_height(const vector<vector<int>>& rows) noexcept;

        // Retrieves the width (of the first row) of the grid.
        // Assumes height > 0.
        static int get_width(const vector<vector<int>>& rows) noexcept;

        // Counts paths on a possibly-mutated board from (i, j) to finish
        // that hit every non-blocked cell once. [Helper for count_paths().]
        int dfs(int remaining, int i, int j) noexcept;

        array<array<bool, max_dimension>, max_dimension> cells_ {};
        const int height_, width_;
        int start_remaining_;
        int start_i_ {}, start_j_ {}, finish_i_ {}, finish_j_ {};
    };

    Board::Board(const vector<vector<int>>& rows) noexcept
        : height_{get_height(rows)}, width_{get_width(rows)},
          start_remaining_{height_ * width_ - 1}
    {
        for (auto i = 0; i != height_; ++i) {
            for (auto j = 0; j != width_; ++j) {
                switch (rows[i][j]) {
                case 0:
                    break;
                case -1:
                    cells_[i][j] = true;
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
        const auto height = static_cast<int>(size(rows));
        assert(height <= max_dimension);
        return height;
    }

    inline int Board::get_width(const vector<vector<int>>& rows) noexcept
    {
        using std::size;
        const auto width = static_cast<int>(size(rows.front()));
        assert(width <= max_dimension);
        return width;
    }

    int Board::dfs(const int remaining, const int i, const int j) noexcept
    {
        if (i == -1 || i == height_ || j == -1 || j == width_ || cells_[i][j])
            return 0;

        const auto filled = remaining == 0;
        const auto at_end = i == finish_i_ && j == finish_j_;
        if (filled || at_end) return +(filled && at_end);

        cells_[i][j] = true;

        const auto sum = dfs(remaining - 1, i, j - 1)
                       + dfs(remaining - 1, i, j + 1)
                       + dfs(remaining - 1, i - 1, j)
                       + dfs(remaining - 1, i + 1, j);

        cells_[i][j] = false;

        return sum;
    }
}

int Solution::uniquePathsIII(const vector<vector<int>>& rows) noexcept
{
    return Board{rows}.count_paths();
}
