#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

namespace {
    std::vector<int> read_values()
    {
        std::vector<int>::size_type n {};
        std::cin >> n;
        
        std::vector<int> a;
        for (a.reserve(n); n != 0u; --n) {
            auto k = 0;
            std::cin >> k;
            a.push_back(k);
        }

        return a;
    }

    std::map<int, std::vector<int>::size_type>
    get_val_pos_map(const std::vector<int>& a)
    {
        std::map<int, std::vector<int>::size_type> m;
        for (decltype(a.size()) i {0u}; i != a.size(); ++i)
            m[a[i]] = i;

        return m;
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        const auto a = read_values();

        auto b = a;
        std::sort(std::begin(b), std::end(b));
        const auto m = get_val_pos_map(b);

        auto sep = "";
        for (const auto k : a)  {
            std::cout << sep << m.at(k);
            sep = " ";
        }

        std::cout << '\n';
    }
}
