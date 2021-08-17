#include <algorithm>
#include <array>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace {
    inline bool is_vowel(const char c)
    {
        switch (c) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;

        default:
            return false;
        }
    }

    inline void decompose(const std::string& s, std::vector<char>& vowels,
                                                std::vector<char>& consonants)
    {
        for (const auto c : s)
            (is_vowel(c) ? vowels : consonants).push_back(c);
    }

    void ygritte_sort(std::string& s)
    {
        if (s.empty()) return;

        // place vowels and consonants in separate sorted groups
        std::array<std::vector<char>, 2u> a;
        for (auto& g : a) g.reserve(s.size());
        decompose(s, a.front(), a.back());
        for (auto& g : a) std::sort(std::begin(g), std::end(g));

        // prepare to interleave vowels and consonants
        if (!is_vowel(s.front())) std::swap(a.front(), a.back());
        const auto min_size = std::min(a.front().size(), a.back().size());
        s.clear();

        // build the interleaved portion of the new string
        for (std::vector<char>::size_type i {0u}; i != min_size; ++i) {
            s += a.front()[i];
            s += a.back()[i];
        }

        // append the remaining characters
        for (const auto& g : a)
            for (auto i = min_size; i != g.size(); ++i) s += g[i];
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        ygritte_sort(s);
        std::cout << s << '\n';
    }
}
