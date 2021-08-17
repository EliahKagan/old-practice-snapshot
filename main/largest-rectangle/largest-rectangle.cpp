#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

namespace {
    using Index = std::vector<long long>::size_type;

    std::vector<long long> read_histogram()
    {
        Index n {};
        std::cin >> n;

        std::vector<long long> h;
        h.reserve(n + 2u);
        h.push_back(0LL); // brackets the histogram on the left

        while (n-- != 0u) {
            auto x = 0LL;
            std::cin >> x;
            h.push_back(x);
        }

        h.push_back(0LL); // brackets the histogram on the right
        return h;
    }

    long long compute_max_area(const std::vector<long long>& h)
    {
        std::stack<Index> lefts;
        auto acc = 0LL;

        for (Index right {0u}; right != h.size(); ++right) {
            while (!lefts.empty() && h[lefts.top()] > h[right]) {
                const auto left = lefts.top();
                lefts.pop();

                auto width = right;
                if (!lefts.empty()) width -= 1u + lefts.top();

                acc = std::max(acc, h[left] * static_cast<long long>(width));
            }

            lefts.push(right);
        }

        return acc;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    std::cout << compute_max_area(read_histogram()) << '\n';
}
