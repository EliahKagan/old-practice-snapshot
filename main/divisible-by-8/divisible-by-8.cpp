#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <string>

namespace {
    inline std::string get_word()
    {
        std::string s;
        std::cin >> s;
        return s;
    }

    inline bool is_divisible_by_8(std::string&& n) // brute-force algorithm
    {
        constexpr auto mask = 7;

        const auto n_begin = std::begin(n), n_end = std::end(n);

        std::sort(n_begin, n_end);
        do
            if ((std::atoi(n.c_str()) & mask) == 0) return true;
        while (std::next_permutation(n_begin, n_end));

        return false;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t)
        std::cout << (is_divisible_by_8(get_word()) ? "Yes" : "No") << '\n';
}
