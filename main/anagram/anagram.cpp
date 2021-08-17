#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>

namespace {
    bool are_anagrams(std::string&& s, std::string&& t)
    {
        if (s.size() != t.size()) return false; // a simple optimization

        std::sort(std::begin(s), std::end(s));
        std::sort(std::begin(t), std::end(t));
        return s == t;
    }
}

int main()
{
    auto n = 0;
    for (std::cin >> n; n > 0; --n) {
        std::string s, t;
        std::cin >> s >> t;
        std::cout << (are_anagrams(std::move(s), std::move(t)) ? "YES" : "NO")
                  << '\n';
    }
}
