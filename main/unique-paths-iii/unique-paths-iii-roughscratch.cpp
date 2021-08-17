class Solution {
public:
    static int uniquePathsIII(const vector<vector<int>>& grid) noexcept;
};

namespace {
    constexpr size_t max_dimension {20};

    using Board = array<array<bool, max_dimension>, max_dimension>;

    template<typename Rows>
    inline int get_height(const Rows& rows) noexcept
    {
        using std::size;
        return static_cast<int>(size(rows));
    }

    template<typename Rows>
    inline int get_width(const Rows& rows) noexcept // Assumes height > 0.
    {
        using std::size;
        return static_cast<int>(size(rows.front()));
    }

    // Populates a board, which is presumed to be zero-initialized.
    // Returns start_i, start_j, finish_i, finish_j, obstacle_count.
    tuple<int, int, int, int, int>
    populate_board(const vector<vector<int>>& grid, Board& board) noexcept
    {
        const auto height = get_height(grid);
        const auto width = get_width(grid);
        assert(height < max_dimension && width < max_dimension);

        int start_i {}, start_j {}, finish_i {}, finish_j {};
        auto obstacle_count = 0;

        for (auto i = 0; i != height; ++i) {
            for (auto j = 0; j != width; ++j) {
                switch (grid[i][j]) {
                case 0:
                    break;
                case -1:
                    board[i][j] = true;
                    ++obstacle_count;
                    break;
                case 1:
                    start_i = i;
                    start_j = j;
                    break;
                case 2:
                    finish_i = i;
                    finish_j = j;
                    break;
                default:
                    abort();
                }
            }
        }

        return {start_i, start_j, finish_i, finish_j, obstacle_count};
    }

    int count_paths(Board& board, const int start_i, const int start_j,
                    const int finish_i, const int finish_j,
                    const int unobstructed_count) noexcept
    {
        const auto dfs = [
                &board, height = get_height(board), width = get_width(board),
                finish_i, finish_j](const auto& me, const int remaining,
                                    const int i, const int j) noexcept -> int {
            if (i == -1 || i == height || j == -1 || j == width || board[i][j])
                return 0;

            const auto filled = remaining == 0;
            const auto at_end = i == finish_i && j == finish_j;
            if (filled || at_end) return filled && at_end ? 1 : 0;

            board[i][j] = true;

            const auto sum = me(me, remaining - 1, i, j - 1)
                           + me(me, remaining - 1, i, j + 1)
                           + me(me, remaining - 1, i - 1, j)
                           + me(me, remaining - 1, i + 1, j);

            board[i][k] = false;

            return sum;
        };

        return dfs(dfs, unobstructed_count - 1, start_i, start_j);
    }
}

int Solution::uniquePathsIII(const vector<vector<int>>& grid) noexcept
{
    Board board {};
    const auto [start_i, start_j, finish_i, finish_j, obstacle_count] =
            populate_board(grid, board);

    const auto area = get_height(board) * get_width(board);

    return count_paths(board, start_i, start_j, finish_i, finish_j,
                       area - obstacle_count);
}
