#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <numeric>
#include <queue>
#include <vector>

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

namespace {
    void test(const int max_projects, const int principal,
              const std::vector<int>& profits, const std::vector<int>& capital)
    {
        std::cout << Solution::findMaximizedCapital(max_projects, principal,
                                                    profits, capital) << '\n';
    }
}

int main()
{
    test(2, 0, {1, 2, 3}, {0, 1, 1});

    test(5, 10, {100, 90, 70, 80, 40, 20, 10, 1000},
                {100, 20, 30, 10, 50, 5, 5, 350});

    test(5, 10, {100, 90, 70, 80, 40, 20, 10, 1000},
                {100, 20, 30, 10, 50, 5, 5, 351});

    test(6, 10, {100, 90, 70, 80, 40, 20, 10, 1000},
                {100, 20, 30, 10, 50, 5, 5, 351});
}
