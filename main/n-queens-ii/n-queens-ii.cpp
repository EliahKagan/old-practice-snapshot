class Solution {
public:
    static int totalNQueens(size_t n);
};

int Solution::totalNQueens(const size_t n)
{
    if (n == 0u) return 1u;

    vector<size_t> path;
    path.reserve(n);
    path.push_back(0u);
    auto count = 0;

    // (i, j) and (h, k) share a column iff j == k.
    // (i, j) and (h, k) share a '/' diagonal iff i + j == h + k.
    // (i, j) and (h, k) share a '\' diagonal iff i + k == h + j.
    const auto ok = [&path](const size_t j) {
        const auto i = path.size() - 1u;

        for (size_t h {0u}; h != i; ++h) {
            const auto k = path[h];
            if (j == k || i + j == h + k || i + k == h + j) return false;
        }

        return true;
    };

    for (; ; ) {
        const auto j = path.back();

        if (j == n) {
            path.pop_back();
            if (path.empty()) break;
        }
        else if (ok(j)) {
            if (path.size() == n) {
                ++count;
            } else {
                path.push_back(0u);
                continue; // so we don't increment the newly pushed index
            }
        }

        ++path.back();
    }

    return count;
}
