class Solution {
public:
    static int findMaximizedCapital(int max_projects, int principal,
                                    const std::vector<int>& profits,
                                    const std::vector<int>& capital);
};

namespace {
    using std::size_t;

    std::vector<size_t> get_sorted_indices(const std::vector<int>& values)
    {
        std::vector<size_t> indices (values.size());
        const auto first = std::begin(indices), last = std::end(indices);

        std::iota(first, last, size_t{});

        std::sort(first, last,
                  [&values](const size_t i, const size_t j) noexcept {
                      return values[i] < values[j];
                  });

        return indices;
    }
}

int Solution::findMaximizedCapital(int max_projects, int principal,
                                   const std::vector<int>& profits,
                                   const std::vector<int>& capital)
{
    assert(profits.size() == capital.size());

    const auto indices = get_sorted_indices(capital);
    const auto last = std::cend(indices);
    auto first = std::cbegin(indices);

    std::priority_queue<int> heap;

    while (max_projects-- > 0) {
        for (; first != last && capital[*first] <= principal; ++first)
            heap.push(profits[*first]);

        if (heap.empty()) break;

        principal += heap.top();
        heap.pop();
    }

    return principal;
}
