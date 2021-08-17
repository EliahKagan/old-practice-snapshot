#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
    template<typename It>
    using Value = typename std::iterator_traits<It>::value_type;

    template<typename T>
    constexpr auto is_integral_v = std::is_integral<T>::value;

    template<typename It>
    constexpr void insertion_sort(const It first, const It last) noexcept
    {
        if (first == last) return;

        for (auto right = first + 1; right != last; ++right) {
            auto elem = std::move(*right);

            auto left = right;
            for (; left != first && elem < left[-1]; --left)
                *left = std::move(left[-1]);

            *left = std::move(elem);
        }
    }

    template<typename It>
    void bucket_sort(const It first, const It last) noexcept
    {
        static_assert(is_integral_v<Value<It>>,
                "this bucket sort implementation is for integral types");

        const auto len = last - first;
        if (len == 0) return;

        // Compute range information that will be used for bucket selection.
        const auto minmax = std::minmax_element(first, last);
        const auto minval = *minmax.first, maxval = *minmax.second;
        const auto range = static_cast<double>(maxval - minval + 1);

        // Make the buckets.
        using Buckets = std::vector<std::vector<Value<It>>>;
        using Index = typename Buckets::size_type;
        Buckets buckets (static_cast<Index>(len));

        // Copy the elements into their buckets.
        std::for_each(first, last, [&](const Value<It> elem) noexcept {
            const auto point = static_cast<double>(elem - minval) / range;
            buckets.at(static_cast<Index>(point)).push_back(elem);
        });

        // Copy the elements back.
        auto pos = first;
        for (const auto& bkt : buckets)
            pos = std::copy(cbegin(bkt), cend(bkt), pos);
        assert(pos == last);

        // Perform the final insertion sort.
        insertion_sort(first, last);
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
    bucket_sort(begin(a), end(a));
    print(a);
}
