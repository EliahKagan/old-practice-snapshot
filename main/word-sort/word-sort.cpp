#include <iostream>
#include <numeric>
#include <set>
#include <string>

namespace {
    using Size = typename std::string::size_type;

    Size print_and_add(const std::multiset<Size>& lengths)
    {
        constexpr auto zero = static_cast<Size>(0u);

        const auto adder = [](const Size a, const Size e) {
            std::cout << e << ' ';
            return a + e;
        };

        return std::accumulate(lengths.cbegin(), lengths.cend(), zero, adder);
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::multiset<Size> lengths;

        auto n = 0;
        for (std::cin >> n; n > 0; --n) {
            std::string s;
            std::cin >> s;
            lengths.insert(s.size());
        }

        std::cout << print_and_add(lengths) << '\n';
    }
}
