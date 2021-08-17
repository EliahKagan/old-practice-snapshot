#include <algorithm>
#include <iterator>
#include <iostream>
#include <utility>
#include <vector>

namespace {
    std::vector<int> get()
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

    void put(std::vector<int>&& a)
    {
        auto sep = "";

        for (const auto k : a) {
            std::cout << sep << k;
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        auto a = get();
        std::sort(std::begin(a), std::end(a));
        put(std::move(a));
    }
}
