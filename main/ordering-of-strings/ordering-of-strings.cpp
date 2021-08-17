#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

namespace {
    std::vector<std::string> get()
    {
        typename std::vector<std::string>::size_type n {};
        std::cin >> n;
        
        std::vector<std::string> a;
        for (a.reserve(n); n != 0u; --n) {
            std::string s;
            std::cin >> s;
            a.emplace_back(std::move(s));
        }
        
        return a;
    }
    
    void put_extrema(const std::vector<std::string>& a)
    {
        if (!a.empty()) {
            const auto min_max = std::minmax_element(a.cbegin(), a.cend());
            std::cout << *min_max.first << ' ' << *min_max.second;
        }
        
        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) put_extrema(get());
}
