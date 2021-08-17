#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_map>

namespace {
    std::string::difference_type max_chars_between_same(const std::string& s)
    {
        std::string::size_type max_delta {0u};

        std::unordered_map<char, std::string::size_type> lasts;

        for (auto i = s.size(); i-- != 0u; ) {
            const auto p = lasts.find(s[i]);
            
            if (p == std::end(lasts)) lasts.emplace(s[i], i);
            else max_delta = std::max(max_delta, p->second - i);
        }
        
        return static_cast<std::string::difference_type>(max_delta) - 1;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::string s;
        std::cin >> s;
        std::cout << max_chars_between_same(s) << '\n';
    }
}
