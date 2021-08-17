#include <cstddef>
#include <iostream>
#include <vector>

namespace {
    std::vector<std::size_t> get()
    {
        std::vector<std::size_t>::size_type n {};
        std::cin >> n;

        std::vector<std::size_t> a;
        for (a.reserve(n); n != 0u; --n) {
            std::size_t k {};
            std::cin >> k;
            a.push_back(k);
        }

        return a;
    }

    void put_rearranged(std::vector<std::size_t>&& a)
    {
        auto sep = "";
        for (const auto k : a) {
            std::cout << sep << a.at(k);
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) put_rearranged(get());
}
