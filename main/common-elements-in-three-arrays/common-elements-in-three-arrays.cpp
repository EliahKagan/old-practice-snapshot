#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace {
    template<typename T>
    std::vector<T> get(typename std::vector<T>::size_type n)
    {
        std::vector<T> a;
        a.reserve(n);

        for (; n != 0u; --n) {
            T x {};
            std::cin >> x;
            a.push_back(x);
        }

        return a;
    }

    template<typename T>
    std::vector<T> intersect(std::vector<T>&& u, std::vector<T>&& v)
    {
        std::vector<T> w;
        std::set_intersection(u.cbegin(), u.cend(), v.cbegin(), v.cend(),
                              std::back_inserter(w));
        return w;
    }

    template<typename T>
    void put(std::vector<T>&& v)
    {
        auto sep = "";
        for (const auto x : v) {
            std::cout << sep << x;
            sep = " ";
        }

        std::cout << '\n';
    }
}

int main()
{
    auto t = 0;
    for (std::cin >> t; t > 0; --t) {
        std::vector<int>::size_type na = 0u, nb = 0u, nc = 0u;
        std::cin >> na >> nb >> nc;
        auto a = get<int>(na), b = get<int>(nb), c = get<int>(nc);
        put(intersect(intersect(std::move(a), std::move(b)), std::move(c)));
    }
}
