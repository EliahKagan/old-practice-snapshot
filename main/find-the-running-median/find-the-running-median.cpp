#include <cstddef>
#include <functional>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <queue>
#include <vector>

namespace {
    using MaxHeap = std::priority_queue<int, std::vector<int>,
                                             std::less<int>>;

    using MinHeap = std::priority_queue<int, std::vector<int>,
                                             std::greater<int>>;

    inline int get()
    {
        auto e = 0;
        std::cin >> e;
        return e;
    }

    inline void add(MaxHeap& low, MinHeap& high, const int e)
    {
        if (e < low.top())  low.push(e);
        else                high.push(e);
    }

    inline void rebalance(MaxHeap& low, MinHeap& high)
    {
        const auto d = static_cast<std::ptrdiff_t>(low.size())
                        - static_cast<std::ptrdiff_t>(high.size());

        if (std::abs(d) == 2) {
            if (d > 0) {
                high.push(low.top());
                low.pop();
            } else {
                low.push(high.top());
                high.pop();
            }
        }
    }

    inline double compute_median(const MaxHeap& low, const MinHeap& high)
    {
        return low.size() == high.size()
                ? (low.top() + high.top()) / 2.0
                : (low.size() > high.size() ? low.top() : high.top());
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto n = get();
    MaxHeap low;
    MinHeap high;

    low.push(get());
    std::cout << std::fixed << std::setprecision(1)
              << static_cast<double>(low.top()) << '\n';

    while (--n != 0) {
        add(low, high, get());
        rebalance(low, high);
        std::cout << compute_median(low, high) << '\n';
    }
}
