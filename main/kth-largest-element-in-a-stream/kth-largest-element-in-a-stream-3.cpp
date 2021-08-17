#include <cstddef>
#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>

namespace {
    using MinHeap = std::priority_queue<int, std::vector<int>,
                                             std::greater<int>>;

    constexpr std::greater<int> comp {};

    inline bool solve_if_trivial(const std::size_t k, const std::size_t n)
    {
        if (k > n) {
            int x;
            for (auto i = n; i != 0u; --i) std::cin >> x;

            for (auto i = n; i != 0u; --i) std::cout << "-1 ";
            std::cout << '\n';

            return true;
        }

        return false;
    }

    // helper function for process_leading_entries()
    inline MinHeap read_leading_entries(std::size_t k)
    {
        std::vector<int> a;
        a.reserve(k);

        // read the first k values into the vector
        for (auto x = 0; k-- != 0u; ) {
            std::cin >> x;
            a.push_back(x);
        }

        // heapify the values into a priority queue
        return MinHeap{comp, std::move(a)};
    }

    inline MinHeap process_leading_entries(std::size_t k)
    {
        auto heap = read_leading_entries(k);

        // none of the first (k - 1) values could have been the kth highest
        while (--k != 0u) std::cout << "-1 ";

        // the kth highest entry has priority (because we have a MIN heap)
        std::cout << heap.top() << ' ';

        return heap;
    }

    inline void process_remaining_entries(MinHeap& heap,
                                          const std::size_t k, std::size_t n)
    {
        auto x = 0;

        for (n -= k; n != 0; --n) {
            std::cin >> x;

            if (x > heap.top()) { // add x, dropping the old priority element
                heap.pop();
                heap.push(x);
            }

            std::cout << heap.top() << ' ';
        }

        std::cout << '\n';
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::size_t k {}, n {};
        std::cin >> k >> n;

        if (solve_if_trivial(k, n)) continue;

        auto heap = process_leading_entries(k);
        process_remaining_entries(heap, k, n);
    }
}
