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

        constexpr BitMatrix(const int height, const int width) noexcept;

        constexpr int height() const noexcept { return height_; }

        constexpr int width() const noexcept { return width_; }

        constexpr int area() const noexcept { return height_ * width_; }

        [[maybe_unused]]
        constexpr bool operator()(int i, int j) const noexcept;

        reference operator()(const int i, const int j) noexcept;

        // Perfect (i.e. unique) hash of the board and specified position.
        int encode_with_position(int i, int j) const noexcept;

    private:
        constexpr int index(const int i, const int j) const noexcept
            { return i * width_ + j; }

        BitSet bits_ {};
        const int height_, width_;
    };

    constexpr BitMatrix::BitMatrix(const int height, const int width) noexcept
            : height_{height}, width_{width}
    {
        assert(area() <= max_area);
    }

    [[maybe_unused]] constexpr bool
    BitMatrix::operator()(const int i, const int j) const noexcept
    {
        return bits_[index(i, j)];
    }

    inline BitMatrix::reference
    BitMatrix::operator()(const int i, const int j) noexcept
    {
        return bits_[index(i, j)];
    }

    inline int
    BitMatrix::encode_with_position(const int i, const int j) const noexcept
    {
        return static_cast<int>(bits_.to_ulong()) | (index(i, j) << max_area);
    }

    class Board {
    public:
        // Initializes and populates the board.
        explicit Board(const vector<vector<int>>& rows) noexcept;

        // Counts start-to-finish paths that hit every non-blocked cell once.
        int count_paths() noexcept;

        // Display instrumentation of memo cache.
        void show_hits() const;

    private:
        // Retrieves the height of the grid.
        static int get_height(const vector<vector<int>>& rows) noexcept;

        // Retrieves the width (of the first row) of the grid.
        // Assumes height > 0.
        static int get_width(const vector<vector<int>>& rows) noexcept;

        // Counts paths on a possibly-mutated board from (i, j) to finish
        // that hit every non-blocked cell once. [Helper for count_paths().]
        int dfs(int remaining, int i, int j) noexcept;

        unordered_map<int, int> memo_ {};
        unordered_map<int, int> hits_ {}; // instruemntation for memo_
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

    void Board::show_hits() const
    {
        for (const auto& [key, freq] : hits_)
            std::cout << key << ": " << freq << '\n';
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

        const auto key = cells_.encode_with_position(i, j);
        const auto it = memo_.find(key);
        if (it != end(memo_)) {
            ++hits_[key];
            return it->second;
        }

        cells_(i, j) = true;

        const auto sum = dfs(remaining - 1, i, j - 1)
                       + dfs(remaining - 1, i, j + 1)
                       + dfs(remaining - 1, i - 1, j)
                       + dfs(remaining - 1, i + 1, j);

        cells_(i, j) = false;

        memo_.emplace(key, sum);
        return sum;
    }
}

int Solution::uniquePathsIII(const vector<vector<int>>& rows) noexcept
{
    auto board = Board{rows};
    const auto count = board.count_paths();
    board.show_hits();
    return count;
}
