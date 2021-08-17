#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
    template<typename It>
    using Delta = typename std::iterator_traits<It>::difference_type;

    template<typename It>
    constexpr void heapsort(const It first, const It last) noexcept
    {
        constexpr Delta<It> no_child {-1};
        auto len = last - first;
        if (len == 0) return;

        const auto pick_child = [first, &len](const Delta<It> parent) noexcept {
            const auto left = parent * 2 + 1;
            if (left >= len) return no_child;

            const auto right = left + 1;
            return right == len || first[left] >= first[right] ? left : right;
        };

        const auto sift_down = [first, pick_child](Delta<It> parent) noexcept {
            auto elem = std::move(first[parent]);

            for (; ; ) {
                const auto child = pick_child(parent);
                if (child == no_child || elem >= first[child]) break;

                first[parent] = std::move(first[child]);
                parent = child;
            }

            first[parent] = std::move(elem);
        };

        // Convert the range into a binary maxheap.
        for (auto parent = len / 2 - 1; parent != -1; --parent)
            sift_down(parent);

        // Build a sorted range right-to-left by popping values from the heap.
        while (--len != 0) {
            std::iter_swap(first, first + len);
            sift_down(0);
        }
    }

    std::vector<int> read_record()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;

        std::vector<int> a (n);
        for (auto& x : a) std::cin >> x;
        return a;
    }

    void print(const std::vector<int>& a)
    {
        std::cout << '[';

        auto sep = "";
        for (const auto x : a) {
            std::cout << sep << x;
            sep = ",";
        }

        std::cout << "]\n";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);

    auto a = read_record();
    heapsort(begin(a), end(a));
    print(a);
}
