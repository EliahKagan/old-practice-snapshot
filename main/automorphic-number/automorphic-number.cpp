#include <iostream>
#include <sstream>
#include <string>

namespace {
    template<typename T>
    std::string to_s(const T x)
    {
        std::ostringstream ss;
        ss << x;
        return ss.str();
    }

    bool ends_with(std::string&& str, std::string&& suf)
    {
        const auto lenstr = str.size(), lensuf = suf.size();
        return lenstr >= lensuf && str.substr(lenstr - lensuf) == suf;
    }

    template<typename T>
    inline bool is_automorphic(const T n)
    {
        return ends_with(to_s(n * n), to_s(n));
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto n = 0;
        std::cin >> n;

        std::cout << (is_automorphic(n) ? "Automorphic" : "Not Automorphic")
                  << '\n';
    }
}
