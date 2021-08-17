class Solution {
public:
    static int maximalSquare(const vector<vector<char>>& matrix);
};

namespace {
    vector<vector<int>> make_grid(const int height, const int width)
    {
        return vector<vector<int>>(height, vector<int>(width));
    }
}

int Solution::maximalSquare(const vector<vector<char>>& matrix)
{
    const auto height = static_cast<int>(matrix.size());
    if (!height) return 0;
    const auto width = static_cast<int>(matrix.front().size());
    if (!width) return 0;
    assert(height > 0 && width > 0);

    auto vertical = make_grid(height, width);
    auto horizontal = make_grid(height, width);
    auto square = make_grid(height, width);
    auto acc = 0;

    // top-left corner (i = 0, j = 0)
    if (matrix[0][0] != '0')
        vertical[0][0] = horizontal[0][0] = square[0][0] = acc = 1;

    // rest of the topmost row (i = 0, j > 0)
    for (auto j = 1; j != width; ++j) {
        if (matrix[0][j] != '0') {
            vertical[0][j] = square[0][j] = acc = 1;
            horizontal[0][j] = horizontal[0][j - 1] + 1;
        }
    }

    for (auto i = 1; i != height; ++i) {
        // rest of the leftmost column (i > 0, j = 0)
        if (matrix[i][0] != '0') {
            vertical[i][0] = vertical[i - 1][0] + 1;
            horizontal[i][0] = square[i][0] = 1;
            acc = max(acc, 1);
        }

        // rest of the matrix (i > 0, j > 0)
        for (auto j = 1; j != width; ++j) {
            if (matrix[i][j] != '0') {
                vertical[i][j] = vertical[i - 1][j] + 1;
                horizontal[i][j] = horizontal[i][j - 1] + 1;

                square[i][j] = min({vertical[i][j],
                                    horizontal[i][j],
                                    square[i - 1][j - 1] + 1});

                acc = max(acc, square[i][j]);
            }
        }
    }

    for (const auto& grid : {vertical, horizontal, square}) {
        for (auto i = 0; i != height; ++i) {
            for (auto j = 0; j != width; ++j)
                cout << ' ' << grid[i][j];

            cout << '\n';
        }

        cout << "---------------------------\n";
    }

    return acc * acc;
}
