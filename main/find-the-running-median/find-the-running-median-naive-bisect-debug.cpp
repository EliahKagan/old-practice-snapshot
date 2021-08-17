#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <vector>

namespace {
    using It = std::vector<int>::iterator;

    inline void add(const It first, const It last, const int value) noexcept
    {
        const auto mid = std::upper_bound(first, last, value);
        std::move_backward(mid, last, last + 1);
        *mid = value;
    }

    inline float median(const It first, const It last) noexcept
    {
        const auto delta = last - first;
        const auto half = delta / 2;

        // FIXME: remove after debugging
        std::cerr << '(' << delta << ") ";
        if (delta % 2 == 0)
            std::cerr << '{' << first[half - 1] << ", " << first[half] << "}\n";
        else
            std::cerr << '{' << first[half] << '}' << '\n';

        return delta % 2 == 0
                ? static_cast<float>(first[half - 1] + first[half]) / 2.0f
                : static_cast<float>(first[half]);
    }

    void print(const std::vector<int>& a)
    {
        std::cerr << '[';

        auto sep = "";
        for (const auto x : a) {
            std::cerr << sep << x;
            sep = " ";
        }

        std::cerr << "] ";
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cout << std::fixed << std::setprecision(1);

    std::vector<int>::size_type n {};
    std::cin >> n;

    std::vector<int> a (n);
    const auto first = begin(a);
    const auto real_last = end(a);

    for (auto last = first; last != real_last; ) {
        int value {};
        std::cin >> value;
        add(first, last, value);
        print(a); // FIXME: remove after debugging
        std::cout << median(first, ++last) << '\n';
    }
}
