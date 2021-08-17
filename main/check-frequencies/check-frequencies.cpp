#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <string>

namespace {
    bool check_frequencies(const std::string& s)
    {
        constexpr std::size_t n {26u};

        std::array<int, n> a {};
        for (const auto c : s) ++a[static_cast<std::size_t>(c - 'a')];
        std::sort(std::begin(a), std::end(a));
        
        std::size_t i {0u};
        while (i != n && a[i] == 0) ++i; // indexes first nonzero frequency

        // all the same letter
        if (n - i < 2u) return true; //-V658

        // all letters appear equally often
        if (a[i] == a[n - 1u]) return true;

        // one letter appears once more often than the others
        if (a[i] == a[n - 2u] && a[n - 1u] - a[i] == 1) return true;

        // one letter appears once; others appear equally often
        if (a[i] == 1 && a[i + 1u] == a[n - 1u]) return true;

        return false;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        std::cout << check_frequencies(s) << '\n';
    }
}
