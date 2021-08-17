#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

namespace {
    std::vector<std::string> get_strings()
    {
        std::vector<std::string>::size_type n {};
        std::cin >> n;

        std::vector<std::string> a;
        a.reserve(n);

        for (std::string s; n != 0u; --n) {
            std::cin >> s;
            a.push_back(std::move(s));
        }

        return a;
    }
}

int main()
{
    auto a = get_strings();

    std::sort(std::begin(a), std::end(a), [](const auto& s, const auto& t) {
        const auto slen = s.size(), tlen = t.size();
        return slen == tlen ? s < t : slen < tlen;
    });

    for (const auto& w : a) std::cout << w << '\n';
}
