#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
    template<typename It>
    constexpr It partition(const It first, const It last) noexcept
    {
        const auto center = first + (last - first) / 2;
        std::iter_swap(first, center);

        const auto pivot = *first;
        auto left = first;

        for (auto right = first + 1; right != last; ++right)
            if (*right < pivot) std::iter_swap(++left, right);

        std::iter_swap(first, left);
        return left;
    }

    template<typename It>
    constexpr void quicksort(const It first, const It last) noexcept
    {
        if (last - first > 1) {
            auto mid = partition(first, last);
            quicksort(first, mid);
            quicksort(++mid, last);
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
    quicksort(begin(a), end(a));
    print(a);
}
