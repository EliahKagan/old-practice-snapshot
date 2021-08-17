#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
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
    insertion_sort(begin(a), end(a));
    print(a);
}
